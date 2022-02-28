#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "driver/gpio.h"

void app_main(void)
{
    // nvs_flash_init();
    // tcpip_adapter_init();
    int level = 0;
    gpio_set_direction(GPIO_NUM_32, GPIO_MODE_OUTPUT);
    while (true) {
        printf("%d", gpio_set_level(GPIO_NUM_32, level));
        level = !level;
        printf("Level: %d\n", level);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}