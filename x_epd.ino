#//pragma once
#include "epd_driver.h"
#include "firasans.h"
//#include "esp_adc_cal.h"

// python3 imgconvert.py -i ~/Bilder/icons8-temperature-inside-50.png -n icon_ti -o ~/Dokumente/Arduino/ESP32_LilyGo_T5_weather/icon_ti.h
#include "zz_icon_to.h"
#include "zz_icon_wi.h"
#include "zz_icon_wl.h"
#include "zz_icon_ti.h"
#include "zz_icon_hu.h"
#include "zz_icon_ra.h"
#include "zz_icon_su.h"

int icon_top = 62;
int icon_1_x = 5;
int icon_1_y = icon_top + 3;
int data_1_x = icon_1_x + 75;
int data_1_y = icon_1_y + 40;
int icon_data_x_offs = 235;
int icon_data_y_offs = 60;


#define BATT_PIN            36
//#define SD_MISO             12
//#define SD_MOSI             13
//#define SD_SCLK             14
//#define SD_CS               15

uint8_t *framebuffer;
//int vref = 1100;

// EPD_WIDTH 960
// EPD_HEIGHT 540

int cursor_x; // = 200;
int cursor_y; // = 250;
int pic_width = 576;
int pic_height = 324;
int x_offs = 20;
int y_offs = EPD_HEIGHT - pic_height;

  Rect_t area1 = {
    .x = 0 + x_offs,
    .y = 0 + y_offs,
    .width = pic_width,
    .height =  pic_height
  };
