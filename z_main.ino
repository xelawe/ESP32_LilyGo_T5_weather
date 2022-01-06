void setup()
{
  init_ser();

  init_epd();

  setupNetwork();

  init_mqtt_local();

  init_tick();

  init_touch();
}


void loop()
{

  //reconnect();
  check_mqtt_reset( );

  if (min_tick) {

    // When reading the battery voltage, POWER_EN must be turned on
    epd_poweron();
    epd_clear();
    //epd_clear_area(area1);
    get_draw_pic();

    display_values();
    display_touch();

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    epd_poweroff();

    // It will turn off the power of the ink screen, but cannot turn off the blue LED light.
    // epd_poweroff();

    //It will turn off the power of the entire
    // POWER_EN control and also turn off the blue LED light

    min_tick = false;
  }

  if (gv_button_changed) {
    epd_poweron();
    display_touch();

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    epd_poweroff();
    gv_button_changed = false;
  }

  
  check_touch();

}
