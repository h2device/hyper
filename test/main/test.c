#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "driver/gpio.h"
/*
void app_main(void)
{
    int level = 0;
    gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT); // was 32
    while (true) {
        printf("%d", gpio_set_level(GPIO_NUM_32, level)); // was 32
        level = !level;
        printf("Level: %d\n", level);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
*/
/*
rst - gpio 27, epd 5
busy - gpio 19, epd 12
clk - gpio 18, epd 11
cs - gpio 16 (RX2), epd 9
dc - gpio 17 (TX2), epd 10
mosi - gpio 25, epd 3
miso - gpio 26, epd 4
*/
void app_main(void)
{
    int level = 0;
    gpio_set_direction(GPIO_NUM_27, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);

    while (true) {
        // gpio_set_level(GPIO_NUM_27, level);
        // gpio_set_level(GPIO_NUM_19, level);
        // gpio_set_level(GPIO_NUM_18, level);
        // gpio_set_level(GPIO_NUM_16, level);
        // gpio_set_level(GPIO_NUM_17, level);
        // gpio_set_level(GPIO_NUM_25, level);
        gpio_set_level(GPIO_NUM_26, level);
        // printf("%d", gpio_set_level(GPIO_NUM_32, level)); // was 32
        printf("Looping %d\n", level);
        level = !level;
        // printf("Level: %d\n", level);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}