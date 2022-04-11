q/**
 *  @filename   :   epdif.cpp
 *  @brief      :   Implements EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "epdif.h"
// #include <SPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/spi_common.h"
#include "driver/gpio.h"

#include "sdkconfig.h"
#include "esp_log.h"

#define EPD_HOST HSPI_HOST

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

void EpdIf::DigitalWrite(int pin, int value) {
    // digitalWrite(pin, value); // ARDUINO
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, value);
}

int EpdIf::DigitalRead(int pin) {
    gpio_set_direction(pin, GPIO_MODE_INPUT);
    return gpio_get_level(pin);
    // return digitalRead(pin); // ARDUINO
}

void EpdIf::DelayMs(unsigned int delaytime) {
    // delay(delaytime);
    vTaskDelay(delaytime);
}

void EpdIf::SpiTransfer(unsigned char data) {
    digitalWrite(CS_PIN, LOW);
    // TODO: Convert to ESP-IDF
    digitalWrite(CS_PIN, HIGH);
    /*
    digitalWrite(CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(CS_PIN, HIGH);
    */
}

int EpdIf::IfInit(void) {
    gpio_set_direction(CS_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(RST_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(DC_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUSY_PIN, GPIO_MODE_INPUT);
    // SPI.begin()
    esp_err_t err;
    spi_device_handle_t spi_handle;

    spi_bus_config_t buscfg = {
        .mosi_io_num = MOSI_PIN,
        .miso_io_num = MISO_PIN,
        .sclk_io_num = CLK_PIN,
    };
    err = spi_bus_initialize(EPD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    assert( err == ESP_OK );

    spi_device_interface_config_t devcfg = {
        .mode = 0,
        .clock_speed_hz = 500 * 1000,
        .spics_io_num = CS_PIN,
        .flags = SPI_TRANS_USE_RXDATA,
        .queue_size = 1
    };
    err = spi_bus_add_device(EPD_HOST, &devcfg, &spi_handle);
    assert( err == ESP_OK );

    /*
    uint8_t cmd = 0x03;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &cmd;

    gpio_set_level(PIN_NUM_SS, 0);
    err = spi_device_transmit(opcn2_handle, &t);
    gpio_set_level(PIN_NUM_SS, 1);
    assert( err == ESP_OK );

    ESP_LOGI(TAG, "response: 0x%02x", t.rx_data[0]);
    */

    // TODO: Convert to ESP-IDF
    /*
    pinMode(CS_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(DC_PIN, OUTPUT);
    pinMode(BUSY_PIN, INPUT); 
    SPI.begin();
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    return 0;
    */

    // SPI.begin();
    gpio_set_direction(MOSI_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_direction(CLK_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_direction(MISO_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    
	// Initialize bus
    spi_device_handle_t spi;
    spi_bus_config_t bus_config={
        .miso_io_num=MISO_PIN,
        .mosi_io_num=MOSI_PIN,
        .sclk_io_num=CLK_PIN,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=4092
    };
    spi_dma_chan_t dma_chan = SPI_DMA_CH_AUTO;
    ret = spi_bus_initialize(VSPI_HOST, bus_config, dma_chan);
    ESP_ERROR_CHECK(ret);
    // Adding Eink to bus
    spi_device_interface_config_t devcfg={
        .clock_speed_hz=2000000,
        .mode=0,
        .spics_io_num=CS_PIN,
        .queue_size=7
    };
    ret=spi_bus_add_device(VSPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);
}