
#include "cy_mqtt_v1.h"
//#include <PubSubClient.h>
#include <ArduinoJson.h> //ArduinoJSON6

//const char* topic_TIME = "ATSH28/DATE/timestamp";
//const char* topic_TEMPA = "ATSH28/AUSSEN/TEMP/1/value";
//const char* topic_WIND = "ATSH28/AUSSEN/WIND/1/value";



const char gc_stopic_TIME[] PROGMEM = "ATSH28/DATE/timestamp";
const char gc_stopic_TempA[] PROGMEM = "ATSH28/AUSSEN/TEMP/1/value";
const char gc_stopic_Wind[] PROGMEM = "ATSH28/AUSSEN/WIND/1/value";
const char gc_stopic_WaterL[] PROGMEM = "ATSH28/AUSSEN/WATERLEVEL/1/value";
const char gc_stopic_Rain24h[] PROGMEM = "ATSH28/AUSSEN/RAIN24H/1/value";
const char gc_stopic_TempI[] PROGMEM = "TempI";
const char gc_stopic_BrghtI[] PROGMEM = "BrghtI";
const char gc_stopic_HumiI[] PROGMEM = "HumiI";
const char gc_stopic_Btn1_Act[] PROGMEM = "Btn1";
const char gc_stopic_Btn2_Act[] PROGMEM = "Btn2";
const char gc_stopic_Btn3_Act[] PROGMEM = "Btn3";
const char gc_stopic_Btn4_Act[] PROGMEM = "Btn4";
const char* const gt_stopic[] PROGMEM = { gc_stopic_TIME, gc_stopic_TempA, gc_stopic_Wind, gc_stopic_TempI, gc_stopic_BrghtI
                                        , gc_stopic_WaterL, gc_stopic_HumiI, gc_stopic_Rain24h
                                        , gc_stopic_Btn1_Act, gc_stopic_Btn2_Act, gc_stopic_Btn3_Act, gc_stopic_Btn4_Act};
char gv_stopic[sizeof(gt_stopic)][MQTT_TOPSZ];

char gv_sbuffer[MQTT_TOPSZ];// buffer for reading the string to (needs to be large enough to take the longest string

char gv_ptopic[MQTT_TOPSZ];

time_t gv_timestamp_mqtt;
boolean gv_timestamp_mqtt_ok = false;

float tempC1;
boolean gv_temp1 = false;

float gv_BrghtI;
boolean gv_BrghtI_ok = false;

float gv_HumiI;
boolean gv_HumiI_ok = false;

float gv_Rain24h;
boolean gv_Rain24h_ok = false;

float tempC2;
boolean gv_temp2 = false;

float gv_wind;
boolean gv_wind_ok;

float gv_waterl;
boolean gv_waterl_ok;

boolean gv_button1_active = false;
boolean gv_button2_active = false;
boolean gv_button3_active = false;
boolean gv_button4_active = false;
boolean gv_button_changed = false;
