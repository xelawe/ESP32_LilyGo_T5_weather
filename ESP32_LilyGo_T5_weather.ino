#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif


// ESP32 Dev Module
// Flash size 16MB
// Part. Scheme Huge App 3MB no OTA/1MB SPIFFS


#define USE_SERIAL Serial
#include <cy_serdebug.h>
#include <cy_serial.h>

#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <SPI.h>
//#include <SD.h>

//#include "cy_ota.h"

void init_ser() {
  cy_serial::start(__FILE__);
}
