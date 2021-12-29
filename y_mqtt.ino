void init_mqtt_local() {
  //  client.setServer(mqtt_server, 1883);
  //  client.setCallback(callback);

  init_mqtt(gv_clientname);

  add_subtopic(mqtt_GetTopic_P(gv_stopic[0], mqtt_pre_none, gv_clientname, get_stopic_ix(0)), callback_time);
  add_subtopic(mqtt_GetTopic_P(gv_stopic[1], mqtt_pre_none, gv_clientname, get_stopic_ix(1)), callback_TempA);
  add_subtopic(mqtt_GetTopic_P(gv_stopic[2], mqtt_pre_none, gv_clientname, get_stopic_ix(2)), callback_Wind);
  add_subtopic(mqtt_GetTopic_P(gv_stopic[3], mqtt_pre_cmnd, gv_clientname, get_stopic_ix(3)), callback_TempI);
  add_subtopic(mqtt_GetTopic_P(gv_stopic[4], mqtt_pre_cmnd, gv_clientname, get_stopic_ix(4)), callback_BrghtI);
}


void callback_time(String topic, byte* message, unsigned int length) {
  Serial.println("Time");
  gv_timestamp_mqtt = payload_to_time_t( message, length);
  gv_timestamp_mqtt_ok = true;
  tick_min();
}

void callback_TempA(String topic, byte* message, unsigned int length) {
  Serial.println("TempA");
  tempC2 = payload_to_float( message, length);
  gv_temp2 = true;
}

void callback_TempI(String topic, byte* message, unsigned int length) {
  Serial.println("TempI");
  tempC1 = payload_to_float( message, length);
  gv_temp1 = true;
}

void callback_Wind(String topic, byte* message, unsigned int length) {
  gv_wind = payload_to_float( message, length);
  gv_wind_ok = true;
}

void callback_BrghtI(String topic, byte* message, unsigned int length) {
  gv_BrghtI = payload_to_float( message, length);
  gv_BrghtI_ok = true;
}

void pub_touch(int iv_button) {
  char buffer[10];
  // dtostrf(iv_button, 0, 0, buffer);
  itoa(iv_button, buffer, 10);
  client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_stat, gv_clientname, (PGM_P)F("Button")), buffer, true);
}

time_t payload_to_time_t( byte* payload, unsigned int length) {
  time_t lv_time_t = 0;

  for (int i = 0; i < length; i++) {
    DebugPrint((char)payload[i]);
  }
  DebugPrintln("");

  for (int i = 0; i < length; i++) {

    lv_time_t = (lv_time_t * 10) + payload[i] - 48;

  }

  DebugPrintln(lv_time_t);

  return lv_time_t;
}

float payload_to_float( byte* payload, unsigned int length) {
  float lv_float = 0;
  float lv_fact = 0;
  float lv_sign = 1;

  for (int i = 0; i < length; i++) {
    DebugPrint((char)payload[i]);
  }
  DebugPrintln("");

  for (int i = 0; i < length; i++) {

    switch (payload[i]) {
      case 45: //"-"
        lv_sign = -1;
        break;

      case 46: // "."
        lv_fact = 1;
        break;

      default:
        lv_float = (lv_float * 10) + payload[i] - 48;
        lv_fact = lv_fact * 10;
        break;
    }

  }

  if (lv_fact > 0) {
    lv_float = lv_float / lv_fact;
  }

  lv_float = lv_float * lv_sign;

  DebugPrintln(lv_float);

  return lv_float;
}

char *get_stopic_ix( int ix ) {
  strcpy_P(gv_sbuffer, (char*)pgm_read_dword(&(gt_stopic[ix])));
  //strcpy_P(gv_buffer, );
  return gv_sbuffer;
}
