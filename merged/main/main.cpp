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

static const char* TAG = "example";

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static adc_atten_t atten = ADC_ATTEN_11db;
static adc_unit_t unit = ADC_UNIT_1;

static esp_adc_cal_characteristics_t *adc_chars;
static adc_bits_width_t width = ADC_WIDTH_BIT_12;
static adc1_channel_t channel_f = ADC1_CHANNEL_6; // GPIO_NUM_34
static adc1_channel_t channel_b = ADC1_CHANNEL_7; // GPIO_NUM_35


static constexpr gpio_num_t SDA = GPIO_NUM_22; // TODO: used to be  GPIO_NUM_2
static constexpr gpio_num_t SCL = GPIO_NUM_23; // TODO: used to be  GPIO_NUM_15
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

extern "C" void app_main() {

    check_efuse(); 
    adc1_config_width(width);
    adc1_config_channel_atten(channel_f, atten);
    adc1_config_channel_atten(channel_b, atten);
    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    // esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);

    printf("$ MPU Driver Example: MPU-I2C\n");
    fflush(stdout);

    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(SDA, SCL, CLOCK_SPEED);

    // Or directly with esp-idf API
    /*
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = SDA;
    conf.scl_io_num = SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = CLOCK_SPEED;
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0));
    */

    MPU_t MPU;  // create a default MPU object
    MPU.setBus(i2c0);  // set bus port, not really needed since default is i2c0
    MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);  // set address, default is AD0_LOW

    // Great! Let's verify the communication
    // (this also check if the connected MPU supports the implementation of chip selected in the component menu)
    while (esp_err_t err = MPU.testConnection()) {
        ESP_LOGE(TAG, "Failed to connect to the MPU, error=%#X", err);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "MPU connection successful!");

    // Initialize
    ESP_ERROR_CHECK(MPU.initialize());  // initialize the chip and set initial configurations
    // Setup with your configurations
    // ESP_ERROR_CHECK(MPU.setSampleRate(50));  // set sample rate to 50 Hz
    // ESP_ERROR_CHECK(MPU.setGyroFullScale(mpud::GYRO_FS_500DPS));
    // ESP_ERROR_CHECK(MPU.setAccelFullScale(mpud::ACCEL_FS_4G));

    // Reading sensor data
    printf("Reading sensor data:\n");
    mpud::raw_axes_t accelRaw;   // x, y, z axes as int16
    mpud::raw_axes_t gyroRaw;    // x, y, z axes as int16
    mpud::float_axes_t accelG;   // accel axes in (g) gravity format
    mpud::float_axes_t gyroDPS;  // gyro axes in (DPS) º/s format
    while (true) {
        // Read
        MPU.acceleration(&accelRaw);  // fetch raw data from the registers
        MPU.rotation(&gyroRaw);       // fetch raw data from the registers
        // MPU.motion(&accelRaw, &gyroRaw);  // read both in one shot
        // Convert
        accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
        gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);
        // Debug
        printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
        printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);
        uint32_t adc_reading_b = 0;
        uint32_t adc_reading_f = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            if (unit == ADC_UNIT_1) {
                adc_reading_b += adc1_get_raw((adc1_channel_t)channel_b);
                adc_reading_f += adc1_get_raw((adc1_channel_t)channel_f);
            }
        }

        adc_reading_b /= NO_OF_SAMPLES;
        adc_reading_f /= NO_OF_SAMPLES;
        //Convert adc_reading to voltage in mV
        uint32_t voltage_b = esp_adc_cal_raw_to_voltage(adc_reading_b, adc_chars);
        uint32_t voltage_f = esp_adc_cal_raw_to_voltage(adc_reading_f, adc_chars);
        printf("B Raw: %d\tVoltage: %dmV\n", adc_reading_b, voltage_b);
        printf("F Raw: %d\tVoltage: %dmV\n", adc_reading_f, voltage_f);
        // printf("weight: %7.2f", force / (accelG.y / 9.81));
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}