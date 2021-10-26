void init_mqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void callback(String topic, byte* message, unsigned int length) {
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  if (topic == topic_TIME) {
    Serial.println("Time");
    gv_timestamp_mqtt = payload_to_time_t( message, length);
    gv_timestamp_mqtt_ok = true;
    tick_min();
  }
  if (topic == topic_TEMPA) {
    Serial.println("TempA");
    tempC2 = payload_to_float( message, length);
    gv_temp2 = true;
  }

    if (topic == topic_WIND) {
    Serial.println("Wind");
    gv_wind = payload_to_float( message, length);
    gv_wind_ok = true;
  }

}

void pub_sens() {

  char buffer[256];
  //dtostrf(fire.NUMFirePIXELS, 0, 0, buffer);

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> jsondoc;

  // Add values in the document
  JsonObject lv_ldr = jsondoc.createNestedObject("AS312");
  //lv_ldr["Status"] = gv_as312_trigger;

  int n  = serializeJson(jsondoc, buffer);

  client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_tele, gv_clientname, (PGM_P)F("SENSOR")), buffer, true);
}


void reconnect() {
  String lv_lwt;
  char lv_lwtc[40];

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    mqtt_clientname = gv_clientname;
    lv_lwt = gv_clientname;
    lv_lwt += "/tele/LWT";
    lv_lwt.toCharArray(lv_lwtc, sizeof(lv_lwtc));
    //Serial.print(lv_lwtc);
    if (client.connect(gv_clientname, mqtt_user, mqtt_pass, lv_lwtc, 0, true, "offline")) {
      client.publish(lv_lwtc, "online", true);

      pub_info2();

      Serial.println("connected");

      client.subscribe(topic_TIME);
      client.subscribe(topic_TEMPA);
            client.subscribe(topic_WIND);
      //client.subscribe(topic_CONFIG);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
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
