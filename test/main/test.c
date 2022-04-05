#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "driver/gpio.h"

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
