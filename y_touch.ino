void check_touch() {
  uint16_t  x, y;
  uint8_t state = 0;

  if (digitalRead(TOUCH_INT)) {
    if (touch.scanPoint()) {
      touch.getPoint(x, y, 0);
      Serial.print(y);
      Serial.print("-");
      Serial.println(x);
      y = EPD_HEIGHT - y;
      if ((x > touch_btn1_x && x < (touch_btn1_x + touch_btn1_w) ) && (y > touch_btn1_y && y < (touch_btn1_y + touch_btn1_h))) {
        state = 1;
      } else if ((x > touch_btn2_x && x < (touch_btn2_x + touch_btn2_w) ) && (y > touch_btn2_y && y < (touch_btn2_y + touch_btn2_h))) {
        state = 2;
      } else if ((x > touch_btn3_x && x < (touch_btn3_x + touch_btn3_w) ) && (y > touch_btn3_y && y < (touch_btn3_y + touch_btn3_h))) {
        state = 3;
      } else if ((x > touch_btn4_x && x < (touch_btn4_x + touch_btn4_w) ) && (y > touch_btn4_y && y < (touch_btn4_y + touch_btn4_h))) {
        state = 4;
      } else {
        state = 0;
        return;
      }

      Serial.print(millis());
      Serial.print(":");
      Serial.println(state);

      if (gv_state != state) {
        pub_touch( state);
        gv_state = state;
      }


      //      epd_poweron();
      //      cursor_x = 20;
      //      cursor_y = 60;
      //      switch (state) {
      //        case 0:
      //          break;
      //        case 1:
      //          break;
      //        case 2:
      //          break;
      //        case 3:
      //          break;
      //        case 4:
      //          break;
      //        default:
      //          break;
      //      }
      //      epd_poweroff();

      while (digitalRead(TOUCH_INT)) {
      }
      while (digitalRead(TOUCH_INT)) {
      }
    }
  }
}



void init_touch() {
  pinMode(TOUCH_INT, INPUT_PULLUP);

  Wire.begin(15, 14);

  if (!touch.begin()) {
    Serial.println("start touchscreen failed");
    while (1);
  }
  Serial.println("Started Touchscreen poll...");

  //Draw Box
  epd_draw_rect(touch_btn1_x, touch_btn1_y, touch_btn1_w, touch_btn1_h, 0, framebuffer);
  cursor_x = touch_btn1_x + 15;
  cursor_y = touch_btn1_y + touch_lbl_y_offs;
  writeln((GFXfont *)&FiraSans, "Btn1", &cursor_x, &cursor_y, framebuffer);

  epd_draw_rect(touch_btn2_x, touch_btn2_y, touch_btn2_w, touch_btn2_h, 0, framebuffer);
  cursor_x = touch_btn2_x + 15;
  cursor_y = touch_btn2_y + touch_lbl_y_offs;
  writeln((GFXfont *)&FiraSans, "Btn2", &cursor_x, &cursor_y, framebuffer);

  epd_draw_rect(touch_btn3_x, touch_btn3_y, touch_btn3_w, touch_btn3_h, 0, framebuffer);
  cursor_x = touch_btn3_x + 15;
  cursor_y = touch_btn3_y + touch_lbl_y_offs;
  writeln((GFXfont *)&FiraSans, "Btn3", &cursor_x, &cursor_y, framebuffer);

  epd_draw_rect(touch_btn4_x, touch_btn4_y, touch_btn4_w, touch_btn4_h, 0, framebuffer);
  cursor_x = touch_btn4_x + 15;
  cursor_y = touch_btn4_y + touch_lbl_y_offs;
  writeln((GFXfont *)&FiraSans, "Btn4", &cursor_x, &cursor_y, framebuffer);

  epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}
