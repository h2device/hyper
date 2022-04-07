/**
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
#include "driver/gpio.h"

#include "sdkconfig.h"
#include "esp_log.h"

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
    send_lines(); // NEED TO PASS IN PARAMETESR HERE
    spi_bus_config_t buscfg={
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };
    //Initialize the SPI bus
    ret = spi_bus_initialize(EEPROM_HOST, &buscfg, SPI_DMA_CH_AUTO);
    // SPI.begin();
    gpio_set_direction(MOSI_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_direction(CLK_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    gpio_set_direction(MISO_PIN, GPIO_MODE_OUTPUT);
    vTaskDelay(100 / portTICK_RATE_MS);
    // SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
    spi_bus_config_t buscfg = {
		.mosi_io_num = DATA_PIN,
		.miso_io_num = 5,
		.sclk_io_num = CLK_PIN,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = SPI_MAX_DMA_LEN,
	};
    // Configuration for the SPI master interface
	spi_device_interface_config_t devcfg = {
		.command_bits = 0,
		.address_bits = 0,
		.dummy_bits = 0,
		.duty_cycle_pos = 128,
		.cs_ena_pretrans = 0,
		.cs_ena_posttrans = 0,
		.clock_speed_hz = 26*1000*1000,
		.mode = 0,
		.spics_io_num = 17,
		.queue_size = 1,
		.flags = 0,
		.pre_cb = NULL,
		.post_cb = NULL,
	};

    spi_bus_initialize(VSPI_HOST, &buscfg, 1);
	spi_bus_add_device(VSPI_HOST, &devcfg, &spi_handle);

    /*
    //Send all the commands
    while (lcd_init_cmds[cmd].databytes!=0xff) {
        lcd_cmd(spi, lcd_init_cmds[cmd].cmd, false);
        lcd_data(spi, lcd_init_cmds[cmd].data, lcd_init_cmds[cmd].databytes&0x1F);
        if (lcd_init_cmds[cmd].databytes&0x80) {
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        cmd++;
    }
    */
	
}