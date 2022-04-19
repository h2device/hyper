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
  Paint paint(image, 0, 0);    // width should be the multiple of 8 
  paint.SetRotate(ROTATE_0);
  Epd epd;
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  printf("epd.Init() started.\n");
  if (epd.Init() != 0) {
    printf("e-Paper init failed\n");
    return;
  }
  printf("epd.Init() completed.\n");
  // Here is where the color changes
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  printf("epd.ClearFrameMemory completed.\n");
  epd.DisplayFrame();
  printf("epd.DisplayFrame completed.\n");
  // WORKS TILL HERE
  paint.SetRotate(ROTATE_0);
  /*
  paint.SetWidth(64);
  paint.SetHeight(64);
  paint.SetRotate(ROTATE_0);
  paint.Clear(UNCOLORED);

  paint.DrawStringAt(100, 50, "test", &std_font, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 100, 50, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame(); 
  */
 
  paint.SetWidth(32);
  paint.SetHeight(96);
  paint.SetRotate(ROTATE_90);
  paint.Clear(COLORED);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "80%", &std_font, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  

  /*paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 8, 130, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame(); */
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  /*
  int x = 1;
  
  while(x) {

    paint.SetWidth(32);
    paint.SetHeight(96);
    paint.SetRotate(ROTATE_90);
    paint.Clear(UNCOLORED);
    // char s[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";

    paint.DrawStringAt(0, 4, "penis", &std_font, COLORED);

    // epd.SetFrameMemory_Partial(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
    // epd.DisplayFrame_Partial();
    epd.SetFrameMemory(paint.GetImage(), 80, 72, paint.GetWidth(), paint.GetHeight());
    vTaskDelay(300 / portTICK_PERIOD_MS);
    epd.DisplayFrame();
    printf("Looping!\n");
    x = 0;
  }
  printf("Done!\n");
  */
  printf("displayed, exiting app_main\n");
  return;
}