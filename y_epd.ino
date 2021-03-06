
void display_values() {
  String disp_str;

  epd_fill_rect(0, 0, EPD_WIDTH, y_offs - 1, 0, framebuffer);
  epd_fill_rect(0, 0, EPD_WIDTH, y_offs - 1, 255, framebuffer);

  if ( gv_timestamp_mqtt_ok == true ) {

    time_t lv_now_utc = gv_timestamp_mqtt;
    time_t lv_now =  myTZ.toLocal(lv_now_utc, &tcr);

    disp_str = String(hour(lv_now)) + ":" + twoDigits(minute(lv_now)) // + ":" + twoDigits(second(lv_now));
               + " " + String(dayStr(weekday(lv_now)))
               + " " + String(day(lv_now)) + "." +  String(month(lv_now)) + "." + String(year(lv_now));

    int cursor_dt_x = 20;
    int cursor_dt_y = 50;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
    //String datenow = String(dayStr(weekday(lv_now)));
    //writeln((GFXfont *)&FiraSans, (char *)timenow.c_str(), framebuffer);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  epd_draw_hline(0, icon_top, EPD_WIDTH, 0, framebuffer);

  int icon_x = icon_1_x;
  int icon_y = icon_1_y;
  int data_x = data_1_x;
  int data_y = data_1_y;

  Serial.print("Data_X "); Serial.println(data_x);
  if ( gv_temp2 == true ) {
    Rect_t area = { .x = icon_x, .y = icon_y, .width = icon_to_width, .height = icon_to_height };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_to_data, framebuffer);

    disp_str = String(tempC2, 1) + " °C";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }
  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;

  Serial.print("Data_X "); Serial.println(data_x);
  if ( gv_wind_ok == true ) {
    Rect_t area = { .x = icon_x, .y = icon_y, .width = icon_wi_width, .height = icon_wi_height };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_wi_data, framebuffer);

    disp_str = String(gv_wind, 0) + " km/h";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;
  Serial.print("Data_X "); Serial.println(data_x);
  if ( gv_Rain24h_ok ) {
    Rect_t area = { .x = icon_x, .y = icon_y, .width = icon_ra_width, .height = icon_ra_height };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_ra_data, framebuffer);

    disp_str = String(gv_Rain24h, 1) + " mm";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;
  Serial.print("Data_X "); Serial.println(data_x);
  if ( gv_waterl_ok ) {
    Rect_t area = { .x = icon_x, .y = icon_y, .width = icon_wl_width, .height = icon_wl_height };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_wl_data, framebuffer);

    disp_str = String(gv_waterl, 0) + " cm";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  icon_x = icon_1_x;
  icon_y = icon_1_y + icon_data_y_offs;
  data_x = data_1_x;
  data_y = data_1_y + icon_data_y_offs;

  if ( gv_temp1 == true ) {

    Rect_t area = {
      .x = 5,
      .y = 121,
      .width = icon_ti_width,
      .height =  icon_ti_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_ti_data, framebuffer);

    disp_str = String(tempC1, 1) + " °C";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;
  if (gv_HumiI_ok) {
    Rect_t area = {
      .x = 240,
      .y = 121,
      .width = icon_hu_width,
      .height =  icon_hu_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_hu_data, framebuffer);

    disp_str = String(gv_HumiI, 0) + " %";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;
  //    Rect_t area = {
  //      .x = 475,
  //      .y = 121,
  //      .width = icon_??_width,
  //      .height =  icon_??_height
  //    };
  //    epd_copy_to_framebuffer(area, (uint8_t *) icon_??_data, framebuffer);

  icon_x = icon_x + icon_data_x_offs;
  data_x = data_x + icon_data_x_offs;
  if (gv_BrghtI_ok) {

    Rect_t area = {
      .x = 710,
      .y = 121,
      .width = icon_su_width,
      .height =  icon_su_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_su_data, framebuffer);

    disp_str = String(gv_BrghtI, 0) + " lx";
    int cursor_dt_x = data_x;
    int cursor_dt_y = data_y;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //epd_draw_hline(0, y_offs - 1, 699, 0, framebuffer);
  epd_draw_hline(0, y_offs - 1, 960, 0, framebuffer);

}

void draw_button(int touch_btn_x, int touch_btn_y, int touch_btn_w, int touch_btn_h, boolean btn_active ) {
  //Draw Box
  epd_draw_rect(touch_btn_x, touch_btn_y, touch_btn_w, touch_btn_h, 255, framebuffer);
  epd_draw_rect(touch_btn_x, touch_btn_y, touch_btn_w, touch_btn_h, 0, framebuffer);

  //fill Box
  int color = 0;

  epd_fill_rect(touch_btn_x + 1 , touch_btn_y + 1, touch_btn_w - (1 * 2) , touch_btn_h - (1 * 2), 0, framebuffer);
  epd_fill_rect(touch_btn_x + 1 , touch_btn_y + 1, touch_btn_w - (1 * 2) , touch_btn_h - (1 * 2), 255, framebuffer);

  for (int i = 1; i < 16; i++) {
    color = color + 12;
    if (!btn_active) {
      epd_draw_hline(touch_btn_x + i, touch_btn_y + touch_btn_h - i, touch_btn_w - (i * 2), color, framebuffer);
      epd_draw_vline(touch_btn_x + touch_btn_w - i, touch_btn_y + i, touch_btn_h - (i * 2), color, framebuffer);
    } else {
      epd_draw_hline(touch_btn_x + i, touch_btn_y + i, touch_btn_w - (i * 2), color, framebuffer);
      epd_draw_vline(touch_btn_x + i, touch_btn_y + i, touch_btn_h - (i * 2), color, framebuffer);
    }
  }

  epd_draw_line(touch_btn_x + 1 , touch_btn_y + 1, touch_btn_x + touch_btn_w - (1 * 2) , touch_btn_y + touch_btn_h - (1 * 2), 128, framebuffer);
  epd_fill_rect(touch_btn_x + 16 , touch_btn_y + 16, touch_btn_w - (16 * 2) , touch_btn_h - (16 * 2), color + 30, framebuffer);

  //cursor_x = touch_btn_x + 15;
  //cursor_y = touch_btn_y + touch_lbl_y_offs;
  //writeln((GFXfont *)&FiraSans, "Btn1", &cursor_x, &cursor_y, framebuffer);
}

/** Draw the pixels to the screen

    @param  char *data    A char array
    @param  size_t len    Length of the char array
    @param  boolean start True if the begin of a new screen

*/
void drawPixels(char *data, size_t len, boolean start) {

  int start_line = 0;
  int end_line = pic_height + 1;

  static int x;
  static int y;

  if (start) {
    x = 0;
    y = 0;

    //epd_clear_area(area1);
    //epd_fill_rect(area1.x, area1.y, area1.width, area1.height, 0, framebuffer);
    //epd_fill_rect(area1.x, area1.y, area1.width, area1.height, 255, framebuffer);

    Serial.print("Printing ");
  }

  int color;

  // Serial.println(String("Printing ") + len + " Bytes to the screen");
  Serial.print(len);
  Serial.print(" ");
  for (size_t i = 0; i < len; i++) {

    for (int b = 7; b >= 0; b--) {
      int bit = bitRead(data[i], b);
      if ( y > start_line && y < end_line ) {
        if (bit == 1) {
          color = 0; // Black
        } else {
          color = 255; // White
        }
        //epd_fill_circle(x + x_offs, y + y_offs - start_line, 1, color, framebuffer);
        epd_draw_pixel(x + x_offs, y + y_offs - start_line, color, framebuffer);
      }

      x++;
      if  (x >= pic_width) {
        y++;
        x = 0;
      }

    }
  }

}

void init_epd( ) {

  epd_init();

  epd_poweron();
  epd_clear();


  framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
  if (!framebuffer) {
    Serial.println("alloc memory failed !!!");
    while (1);
  }
  memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

  //epd_fill_circle(740, 450, 3, 0, framebuffer);

  epd_draw_grayscale_image(epd_full_screen(), framebuffer);
  epd_poweroff();

}
