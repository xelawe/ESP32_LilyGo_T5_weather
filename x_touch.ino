#include <touch.h>
#define TOUCH_INT   13
TouchClass touch;

int gv_state = 0;
unsigned long gv_touch_off_ms = 0;


int touch_btn1_x = 600;
int touch_btn1_y = y_offs + 4;
int touch_btn1_w = 170;
int touch_btn1_h = 150;

int touch_btn2_x = touch_btn1_x + touch_btn1_w + 15;
int touch_btn2_y = touch_btn1_y;
int touch_btn2_w = touch_btn1_w;
int touch_btn2_h = touch_btn1_h;

int touch_btn3_x = touch_btn1_x;
int touch_btn3_y = touch_btn1_y + touch_btn1_h + 15;
int touch_btn3_w = touch_btn1_w;
int touch_btn3_h = touch_btn1_h;

int touch_btn4_x = touch_btn3_x + touch_btn3_w + 15;
int touch_btn4_y = touch_btn3_y;
int touch_btn4_w = touch_btn1_w;
int touch_btn4_h = touch_btn1_h;


int touch_lbl_y_offs = 70;
