#include <Arduino.h>
#include <esp_task_wdt.h>

#include "task_manager.h"

void setup() {
  esp_task_wdt_init(60, true);  // time in seconds
  enableLoopWDT();

  Serial.begin(115200);
  delay(100);

  // put your setup code here, to run once:
  Serial.println("Setup 1");
  createTask2();
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("loop 1");
  delay(1000);
}
