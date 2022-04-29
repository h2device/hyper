#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "epd2in9_V2.h"
#include "epdpaint.h"
// #include "imagedata.h"
// #include "fonts.h"

#define COLORED     0
#define UNCOLORED   1

extern "C" void app_main() {
  printf("Good morning!");
  unsigned char image[1024];
  Paint paint(image, 32, 96);    // width should be the multiple of 8 
  paint.SetRotate(ROTATE_90);
  Epd epd;
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  printf("epd.Init() started.\n");
  if (epd.Init() != 0) {
    printf("e-Paper init failed\n");
    return;
  }
  // Here is where the color changes
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  vTaskDelay(2000 / portTICK_PERIOD_MS);
  // int x = 0;
  while(true) {
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 10, "H2D", &font16, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 70, 100, paint.GetWidth(), paint.GetHeight());
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 10, "10%", &font16, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 300, 100, paint.GetWidth(), paint.GetHeight());
      paint.Clear(UNCOLORED);
      paint.DrawStringAt(0, 10, "100mL", &font16, COLORED);
      epd.SetFrameMemory(paint.GetImage(), 530, 100, paint.GetWidth(), paint.GetHeight());
      // epd.SetFrameMemory(paint.GetImage(), 200, 50, paint.GetWidth(), paint.GetHeight());
      epd.DisplayFrame();
      vTaskDelay(300 / portTICK_PERIOD_MS);
  }
  /*
  H2D
  Battery Percentage: 80 %
  Water Volume: 500 mL
  */
  /*
    paint.Clear(UNCOLORED);
    char display_text[5];
    sprintf(display_text, "%d%%", (int) x);
    // paint.DrawStringAt(0, 4, display_text, &std_font, COLORED);
    // epd.SetFrameMemory(paint.GetImage(), 64, 16, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    x++;
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
  */
  printf("Done!\n");
  printf("displayed, exiting app_main\n");
  return;
}