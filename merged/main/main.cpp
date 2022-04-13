// =========================================================================
// Released under the MIT License
// Copyright 2017-2018 Natanael Josue Rabello. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

/**
 * @file mpu_i2c.cpp
 * Example on how to setup MPU through I2C for basic usage.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "I2Cbus.hpp"
#include "MPU.hpp"
#include "mpu/math.hpp"
#include "mpu/types.hpp"

#include "driver/adc.h"
#include "esp_adc_cal.h"

// #include "epd2in9_V2.h"
// #include "epdpaint.h"
// #include "imagedata.h"
// #include "fonts.h"

static const char* TAG = "FINAL";

#define DEFAULT_VREF  1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64

static adc_atten_t atten = ADC_ATTEN_11db;
// static adc_unit_t unit = ADC_UNIT_1;

static esp_adc_cal_characteristics_t *adc_chars;
static adc_bits_width_t width = ADC_WIDTH_BIT_12;
static adc1_channel_t channel_f = ADC1_CHANNEL_3; // GPIO_NUM_39 - SENSOR_VN
static adc1_channel_t channel_b = ADC1_CHANNEL_0; // GPIO_NUM_36 - SENSOR_VP

static constexpr gpio_num_t SDA = GPIO_NUM_22;
static constexpr gpio_num_t SCL = GPIO_NUM_23;
static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

static void check_efuse(void) {
    //Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }
    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static float voltage_to_battery_percentage(int voltage) {
    float battery_voltage = voltage * 2.0 / 1000;
    float percentage_left = 100 - ((battery_voltage - 4.2) * 100 / -1.2);
    if (percentage_left > 99) percentage_left = 99;
    if (percentage_left < 1) percentage_left = 1;
    return percentage_left;
}

static float voltage_to_mass_value(int voltage) {
    float force_value = voltage / 2;
    return force_value;
}

extern "C" void app_main() {
    // Initialize display
    /*
    unsigned char image[1024];
    Paint paint(image, 0, 0);    // width should be the multiple of 8 
    paint.SetRotate(ROTATE_0);
    Epd epd;
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("epd.Init() started.\n");
  if (epd.Init() != 0) {
    printf("e-Paper init failed\n");
    return;
  }
    */
    check_efuse(); 
    adc1_config_width(width);
    adc1_config_channel_atten(channel_f, atten);
    adc1_config_channel_atten(channel_b, atten);
    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));

    printf("$ MPU Driver Example: MPU-I2C\n");
    fflush(stdout);

    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(SDA, SCL, CLOCK_SPEED);

    MPU_t MPU;
    MPU.setBus(i2c0); 
    MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);

    // Initial Bottle Mass
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    uint32_t adc_reading_f_initial = adc1_get_raw((adc1_channel_t)channel_f);
    uint32_t voltage_f_initial = esp_adc_cal_raw_to_voltage(adc_reading_f_initial, adc_chars);
    float bottle_mass = voltage_to_mass_value(voltage_f_initial);
    printf("Bottle mass: %7.2f\n", bottle_mass);

    // Initializing MPU
    while (esp_err_t err = MPU.testConnection()) {
        ESP_LOGE(TAG, "Failed to connect to the MPU, error=%#X", err);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "MPU connection successful!");
    ESP_ERROR_CHECK(MPU.initialize());

    // Reading sensor data
    // printf("Reading sensor data:\n");
    mpud::raw_axes_t accelRaw;   // x, y, z axes as int16
    mpud::raw_axes_t gyroRaw;    // x, y, z axes as int16
    mpud::float_axes_t accelG;   // accel axes in (g) gravity format
    mpud::float_axes_t gyroDPS;  // gyro axes in (DPS) º/s format

    while (true) {
        // IMU PART
        MPU.acceleration(&accelRaw);  // fetch raw data from the registers
        MPU.rotation(&gyroRaw);       // fetch raw data from the registers
        // MPU.motion(&accelRaw, &gyroRaw);  // read both in one shot
        // Convert
        accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
        gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);
        printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);

        // ADC PART
        uint32_t adc_reading_b = 0;
        uint32_t adc_reading_f = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            adc_reading_b += adc1_get_raw((adc1_channel_t)channel_b);
            adc_reading_f += adc1_get_raw((adc1_channel_t)channel_f);
        }

        adc_reading_b /= NO_OF_SAMPLES;
        adc_reading_f /= NO_OF_SAMPLES;
        //Convert adc_reading to voltage in mV
        uint32_t voltage_b = esp_adc_cal_raw_to_voltage(adc_reading_b, adc_chars);
        uint32_t voltage_f = esp_adc_cal_raw_to_voltage(adc_reading_f, adc_chars);

        float percentage_left = voltage_to_battery_percentage(voltage_b);
        float water_mass = voltage_to_mass_value(voltage_f);

        printf("B Raw: %d\tVoltage: %dmV\n", adc_reading_b, voltage_b);
        printf("Battery %% left: %2.2f %%\n\n", percentage_left);

        printf("F Raw: %d\tVoltage: %dmV\n", adc_reading_f, voltage_f);
        printf("Volume in water bottle: %7.2f\n\n", water_mass / (accelG.y / 9.81));

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}