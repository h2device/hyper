#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static const adc_atten_t atten = ADC_ATTEN_11db;
static const adc_unit_t unit = ADC_UNIT_1;

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_channel_t channel_f = ADC1_CHANNEL_6;
static const adc_channel_t channel_b = ADC1_CHANNEL_7;

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

void app_main(void) {

    // Check if Two Point or Vref are burned into eFuse
    check_efuse(); 

    // Configure ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel_f, atten);
    adc1_config_channel_atten(channel_b, atten);

    // Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);

    // Continuously sample ADC1
    while (1) {
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
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}