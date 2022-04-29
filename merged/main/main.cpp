#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

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

#include "epd2in9_V2.h"
#include "epdpaint.h"
#include "imagedata.h"
#include "fonts.h"

static const char* TAG = "FINAL";
#define COLORED     0
#define UNCOLORED   1
#define EMPTY_BOTTLE_VOLTAGE 432 // mV
#define FULL_BOTTLE_VOLTAGE 2245 // mV
#define TOTAL_BOTTLE_CAPACITY 1000 // g
#define BOTTLE_WEIGHT 328 // g

// #define DEFAULT_VREF  adc1_vref_to_gpio() // Used to be 1100
#define DEFAULT_VREF  1100 // Used to be 1100
#define NO_OF_SAMPLES 512 // Used to be 64

static adc_atten_t atten = ADC_ATTEN_11db;
static const adc_unit_t unit = ADC_UNIT_1;

static esp_adc_cal_characteristics_t *adc_chars;
static adc_bits_width_t width = ADC_WIDTH_BIT_12;

static adc1_channel_t channel_f = ADC1_CHANNEL_6; // GPIO_NUM_34
static adc1_channel_t channel_b = ADC1_CHANNEL_0; // GPIO_NUM_36 - SENSOR_VP

static constexpr gpio_num_t SDA = GPIO_NUM_22;
static constexpr gpio_num_t SCL = GPIO_NUM_23;
static constexpr uint32_t CLOCK_SPEED = 400000;  // range from 100 KHz ~ 400Hz

static float voltage_to_battery_percentage(int voltage) {
    float battery_voltage = voltage * 2.0 / 1000;
    float percentage_left = 100 - ((battery_voltage - 4.2) * 100 / -1.2);
    if (percentage_left > 99) percentage_left = 99;
    if (percentage_left < 1) percentage_left = 1;
    return percentage_left;
}

static float voltage_to_mass_value(int voltage) {
    float delta_y = (float) (FULL_BOTTLE_VOLTAGE - EMPTY_BOTTLE_VOLTAGE);
    float delta_x = (float) (TOTAL_BOTTLE_CAPACITY);
    float mass = ((voltage - EMPTY_BOTTLE_VOLTAGE) * delta_x / delta_y) - 200 - BOTTLE_WEIGHT;
    if (mass < 0) mass = 0;
    return mass;
}

extern "C" void app_main() {

    adc1_config_width(width);
    adc1_config_channel_atten(channel_f, atten);
    adc1_config_channel_atten(channel_b, atten);
    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);

    // Display Initialize
    unsigned char image[1024];
    Paint paint(image, 32, 96);
    paint.SetRotate(ROTATE_90);
    Epd epd;
    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return;
    }

    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    // Initialize I2C on port 0 using I2Cbus interface
    i2c0.begin(SDA, SCL, CLOCK_SPEED);
    MPU_t MPU;
    MPU.setBus(i2c0); 
    MPU.setAddr(mpud::MPU_I2CADDRESS_AD0_LOW);

    // Initial Bottle Values
    vTaskDelay(1000 / portTICK_PERIOD_MS);

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
    // int seconds = 0;

    while (true) {
        // IMU PART
        MPU.acceleration(&accelRaw);  // fetch raw data from the registers
        MPU.rotation(&gyroRaw);       // fetch raw data from the registers
        // MPU.motion(&accelRaw, &gyroRaw);  // read both in one shot
        // Convert 
        accelG = mpud::accelGravity(accelRaw, mpud::ACCEL_FS_4G);
        gyroDPS = mpud::gyroDegPerSec(gyroRaw, mpud::GYRO_FS_500DPS);
        printf("accel: [%+6.2f %+6.2f %+6.2f ] (G) \t", accelG.x, accelG.y, accelG.z);
        // printf("gyro: [%+7.2f %+7.2f %+7.2f ] (º/s)\n", gyroDPS[0], gyroDPS[1], gyroDPS[2]);

        // ADC PART
        uint32_t adc_reading_b = 0;
        uint32_t adc_reading_f = 0;

        // Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            adc_reading_b += adc1_get_raw((adc1_channel_t)channel_b);
            adc_reading_f += adc1_get_raw((adc1_channel_t)channel_f);
        }

        adc_reading_b /= NO_OF_SAMPLES;
        adc_reading_f /= NO_OF_SAMPLES;

        // Convert adc_reading to voltage in mV
        uint32_t voltage_b = esp_adc_cal_raw_to_voltage(adc_reading_b, adc_chars);
        uint32_t voltage_f = esp_adc_cal_raw_to_voltage(adc_reading_f, adc_chars);

        float percentage_left = voltage_to_battery_percentage(voltage_b);
        float water_mass = voltage_to_mass_value(voltage_f);
        float water_volume = water_mass;

        // printf("B Raw: %d\tVoltage: %dmV\n", adc_reading_b, voltage_b);
        // printf("Battery %% left: %2.2f %%\n", percentage_left);
        // printf("F Raw: %d\tVoltage: %dmV\n", adc_reading_f, voltage_f);
        printf("Mass: %7.2f g \t Volume: %7.2f \t\n", water_mass, water_volume);

        // DISPLAY PART
        char water_volume_text[10];
        sprintf(water_volume_text, "V: %dmL", (int) water_volume);
        char percentage_left_text[10];
        sprintf(percentage_left_text, "B: %d%%", (int) percentage_left);
        
        // printf("percentage_left_text: %s\n", percentage_left_text);
        // printf("water_volume_text: %s\n", water_volume_text);
    
        paint.Clear(UNCOLORED);
        paint.DrawStringAt(0, 10, "H2D", &font16, COLORED);
        epd.SetFrameMemory(paint.GetImage(), 70, 100, paint.GetWidth(), paint.GetHeight());
        paint.Clear(UNCOLORED);
        paint.DrawStringAt(0, 10, percentage_left_text, &font16, COLORED);
        epd.SetFrameMemory(paint.GetImage(), 300, 100, paint.GetWidth(), paint.GetHeight());
        paint.Clear(UNCOLORED);
        if(abs(accelG.y) > 0.5 || abs(accelG.x) > 0.5 || abs(accelG.z) > 0.5) 
            paint.DrawStringAt(0, 10, "Not flat", &font16, COLORED);
        else
            paint.DrawStringAt(0, 10, water_volume_text, &font16, COLORED);
        epd.SetFrameMemory(paint.GetImage(), 530, 100, paint.GetWidth(), paint.GetHeight());
        epd.DisplayFrame();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}