#include <touch.h>
#define TOUCH_INT   13
TouchClass touch;

uint8_t state = 1;

int touch_btn1_x = 700;
int touch_btn1_y = 7;
int touch_btn1_w = 240;
int touch_btn1_h = 120;

int touch_btn2_x = 700;
int touch_btn2_y = touch_btn1_y + touch_btn1_h + 15;
int touch_btn2_w = touch_btn1_w;
int touch_btn2_h = touch_btn1_h;

int touch_btn3_x = 700;
int touch_btn3_y = touch_btn2_y + touch_btn2_h + 15;
int touch_btn3_w = touch_btn1_w;
int touch_btn3_h = touch_btn1_h;

int touch_btn4_x = 700;
int touch_btn4_y = touch_btn3_y + touch_btn3_h + 15;
int touch_btn4_w = touch_btn1_w;
int touch_btn4_h = touch_btn1_h;

int touch_lbl_y_offs = 70;
