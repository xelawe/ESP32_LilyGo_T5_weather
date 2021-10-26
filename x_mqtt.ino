
#include "cy_mqtt_v1.h"
#include <PubSubClient.h>
#include <ArduinoJson.h> //ArduinoJSON6
//DynamicJsonDocument CONFIG(2048);

const char* topic_TIME = "ATSH28/DATE/timestamp";
const char* topic_TEMPA = "ATSH28/AUSSEN/TEMP/1/value";
const char* topic_WIND = "ATSH28/AUSSEN/WIND/1/value";
//const char* topic_CONFIG = "JSONConfig";
//const char* topic_UP = "PICTURE";



char gv_ptopic[MQTT_TOPSZ];

time_t gv_timestamp_mqtt;
boolean gv_timestamp_mqtt_ok = false;

float tempC2;
boolean gv_temp2 = false;

float gv_wind;
boolean gv_wind_ok;
