# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# compile C with /Users/naveenvivek/.espressif/tools/xtensa-esp32-elf/esp-2021r2-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
C_DEFINES = -DMBEDTLS_CONFIG_FILE=\"mbedtls/esp_config.h\"

C_INCLUDES = -I/Users/naveenvivek/esp/hyper/build/config -I/Users/naveenvivek/esp/esp-idf/components/esp_local_ctrl/include -I/Users/naveenvivek/esp/esp-idf/components/esp_local_ctrl/proto-c -I/Users/naveenvivek/esp/esp-idf/components/esp_local_ctrl/src -I/Users/naveenvivek/esp/esp-idf/components/protocomm/proto-c -I/Users/naveenvivek/esp/esp-idf/components/newlib/platform_include -I/Users/naveenvivek/esp/esp-idf/components/freertos/FreeRTOS-Kernel/include -I/Users/naveenvivek/esp/esp-idf/components/freertos/esp_additions/include/freertos -I/Users/naveenvivek/esp/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include -I/Users/naveenvivek/esp/esp-idf/components/freertos/esp_additions/include -I/Users/naveenvivek/esp/esp-idf/components/esp_hw_support/include -I/Users/naveenvivek/esp/esp-idf/components/esp_hw_support/include/soc -I/Users/naveenvivek/esp/esp-idf/components/esp_hw_support/include/soc/esp32 -I/Users/naveenvivek/esp/esp-idf/components/esp_hw_support/port/esp32/. -I/Users/naveenvivek/esp/esp-idf/components/heap/include -I/Users/naveenvivek/esp/esp-idf/components/log/include -I/Users/naveenvivek/esp/esp-idf/components/lwip/include/apps -I/Users/naveenvivek/esp/esp-idf/components/lwip/include/apps/sntp -I/Users/naveenvivek/esp/esp-idf/components/lwip/lwip/src/include -I/Users/naveenvivek/esp/esp-idf/components/lwip/port/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/lwip/port/esp32/include/arch -I/Users/naveenvivek/esp/esp-idf/components/soc/include -I/Users/naveenvivek/esp/esp-idf/components/soc/esp32/. -I/Users/naveenvivek/esp/esp-idf/components/soc/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/hal/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/hal/include -I/Users/naveenvivek/esp/esp-idf/components/hal/platform_port/include -I/Users/naveenvivek/esp/esp-idf/components/esp_rom/include -I/Users/naveenvivek/esp/esp-idf/components/esp_rom/include/esp32 -I/Users/naveenvivek/esp/esp-idf/components/esp_rom/esp32 -I/Users/naveenvivek/esp/esp-idf/components/esp_common/include -I/Users/naveenvivek/esp/esp-idf/components/esp_system/include -I/Users/naveenvivek/esp/esp-idf/components/esp_system/port/soc -I/Users/naveenvivek/esp/esp-idf/components/esp_system/port/include/private -I/Users/naveenvivek/esp/esp-idf/components/xtensa/include -I/Users/naveenvivek/esp/esp-idf/components/xtensa/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/driver/include -I/Users/naveenvivek/esp/esp-idf/components/driver/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/driver/deprecated -I/Users/naveenvivek/esp/esp-idf/components/esp_pm/include -I/Users/naveenvivek/esp/esp-idf/components/esp_ringbuf/include -I/Users/naveenvivek/esp/esp-idf/components/efuse/include -I/Users/naveenvivek/esp/esp-idf/components/efuse/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/vfs/include -I/Users/naveenvivek/esp/esp-idf/components/esp_wifi/include -I/Users/naveenvivek/esp/esp-idf/components/esp_event/include -I/Users/naveenvivek/esp/esp-idf/components/esp_netif/include -I/Users/naveenvivek/esp/esp-idf/components/esp_eth/include -I/Users/naveenvivek/esp/esp-idf/components/tcpip_adapter/include -I/Users/naveenvivek/esp/esp-idf/components/esp_phy/include -I/Users/naveenvivek/esp/esp-idf/components/esp_phy/esp32/include -I/Users/naveenvivek/esp/esp-idf/components/esp_timer/include -I/Users/naveenvivek/esp/esp-idf/components/protocomm/include/common -I/Users/naveenvivek/esp/esp-idf/components/protocomm/include/security -I/Users/naveenvivek/esp/esp-idf/components/protocomm/include/transports -I/Users/naveenvivek/esp/esp-idf/components/nvs_flash/include -I/Users/naveenvivek/esp/esp-idf/components/spi_flash/include -I/Users/naveenvivek/esp/esp-idf/components/mbedtls/port/include -I/Users/naveenvivek/esp/esp-idf/components/mbedtls/mbedtls/include -I/Users/naveenvivek/esp/esp-idf/components/mbedtls/esp_crt_bundle/include -I/Users/naveenvivek/esp/esp-idf/components/esp_http_server/include -I/Users/naveenvivek/esp/esp-idf/components/http_parser -I/Users/naveenvivek/esp/esp-idf/components/esp-tls -I/Users/naveenvivek/esp/esp-idf/components/esp-tls/esp-tls-crypto -I/Users/naveenvivek/esp/esp-idf/components/protobuf-c/protobuf-c -I/Users/naveenvivek/esp/esp-idf/components/mdns/include -I/Users/naveenvivek/esp/esp-idf/components/console

C_FLAGS = -mlongcalls -Wno-frame-address  -ffunction-sections -fdata-sections -Wall -Werror=all -Wno-error=unused-function -Wno-error=unused-variable -Wno-error=deprecated-declarations -Wextra -Wno-unused-parameter -Wno-sign-compare -ggdb -Og -fmacro-prefix-map=/Users/naveenvivek/esp/hyper=. -fmacro-prefix-map=/Users/naveenvivek/esp/esp-idf=/IDF -fstrict-volatile-bitfields -Wno-error=unused-but-set-variable -fno-jump-tables -fno-tree-switch-conversion -std=gnu99 -Wno-old-style-declaration -D_GNU_SOURCE -DIDF_VER=\"v5.0-dev-1565-g1d77b5b6fd-dirty\" -DESP_PLATFORM -D_POSIX_READER_WRITER_LOCKS

