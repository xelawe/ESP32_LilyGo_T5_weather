
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
  //epd_draw_hline(0, 60, 699, 0, framebuffer);
  epd_draw_hline(0, 60, EPD_WIDTH, 0, framebuffer);


  if ( gv_temp2 == true ) {

    Rect_t area = {
      .x = 5,
      .y = 61,
      .width = icon_to_width,
      .height =  icon_to_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_to_data, framebuffer);

    int cursor_dt_x = 80;
    int cursor_dt_y = 100;

    disp_str = String(tempC2, 1) + " °C";
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  if ( gv_wind_ok == true ) {
    Rect_t area = {
      .x = 240,
      .y = 61,
      .width = icon_wi_width,
      .height =  icon_wi_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_wi_data, framebuffer);


    int cursor_dt_x = 300;
    int cursor_dt_y = 100;

    disp_str = String(gv_wind, 0) + " km/h";
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  Rect_t area = {
    .x = 475,
    .y = 61,
    .width = icon_ra_width,
    .height =  icon_ra_height
  };
  epd_copy_to_framebuffer(area, (uint8_t *) icon_ra_data, framebuffer);

  area = {
    .x = 710,
    .y = 61,
    .width = icon_wl_width,
    .height =  icon_wl_height
  };
  epd_copy_to_framebuffer(area, (uint8_t *) icon_wl_data, framebuffer);

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if ( gv_temp1 == true ) {

    area = {
      .x = 5,
      .y = 121,
      .width = icon_ti_width,
      .height =  icon_ti_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_ti_data, framebuffer);

    disp_str = String(tempC1, 1) + " °C";
    int cursor_dt_x = 80;
    int cursor_dt_y = 160;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  area = {
    .x = 240,
    .y = 121,
    .width = icon_hu_width,
    .height =  icon_hu_height
  };
  epd_copy_to_framebuffer(area, (uint8_t *) icon_hu_data, framebuffer);

  //  area = {
  //    .x = 475,
  //    .y = 121,
  //    .width = icon_hy_width,
  //    .height =  icon_hy_height
  //  };
  //  epd_copy_to_framebuffer(area, (uint8_t *) icon_hy_data, framebuffer);

  if (gv_BrghtI_ok) {

    area = {
      .x = 710,
      .y = 121,
      .width = icon_su_width,
      .height =  icon_su_height
    };
    epd_copy_to_framebuffer(area, (uint8_t *) icon_su_data, framebuffer);

    disp_str = String(gv_BrghtI, 1) + " lx";
    int cursor_dt_x = 785;
    int cursor_dt_y = 160;
    writeln((GFXfont *)&FiraSans, (char *)disp_str.c_str(), &cursor_dt_x, &cursor_dt_y, framebuffer);
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //epd_draw_hline(0, y_offs - 1, 699, 0, framebuffer);
  epd_draw_hline(0, y_offs - 1, 960, 0, framebuffer);

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
