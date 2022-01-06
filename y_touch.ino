void check_touch() {
  uint16_t  x, y;
  int state = 0;

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
      gv_touch_off_ms = millis() + 150;
      Serial.print(gv_touch_off_ms);
      Serial.print(":");
      Serial.println(state);

      if (gv_state != state) {
        gv_state = state;
        pub_touch( gv_state);
      }

      while (digitalRead(TOUCH_INT)) {
      }
      while (digitalRead(TOUCH_INT)) {
      }

    }
  } else {

    if ((gv_state == -1) || (millis() < gv_touch_off_ms )) {
      return;
    }
    gv_state = -1;
    pub_touch( gv_state);
    Serial.print(millis());
    Serial.print(":");
    Serial.print(gv_touch_off_ms);
    Serial.print(":");
    Serial.println(gv_state);
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

  display_touch();

  epd_draw_grayscale_image(epd_full_screen(), framebuffer);
}

void display_touch() {

  draw_button(touch_btn1_x, touch_btn1_y, touch_btn1_w, touch_btn1_h, gv_button1_active );
  draw_button(touch_btn2_x, touch_btn2_y, touch_btn2_w, touch_btn2_h, gv_button2_active );
  draw_button(touch_btn3_x, touch_btn3_y, touch_btn3_w, touch_btn3_h, gv_button3_active );
  draw_button(touch_btn4_x, touch_btn4_y, touch_btn4_w, touch_btn4_h, gv_button4_active );

}
