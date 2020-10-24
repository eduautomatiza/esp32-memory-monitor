#include <Arduino.h>
#include <esp_task_wdt.h>

#include "task_manager.h"

void printMemoryUse(void) {
  static uint32_t m1 = UINT32_MAX, m2 = UINT32_MAX, mh = UINT32_MAX;
  extern TaskHandle_t loopTaskHandle;
  extern TaskHandle_t loop2TaskHandle;

  uint32_t m;
  if (loopTaskHandle != NULL) {
    m = uxTaskGetStackHighWaterMark(loopTaskHandle);
    if (m < m1) {
      m1 = m;
      Serial.printf("%s water mark = %d\n", pcTaskGetTaskName(loopTaskHandle),
                    m);
    }
  }
  if (loop2TaskHandle != NULL) {
    m = uxTaskGetStackHighWaterMark(loop2TaskHandle);
    if (m < m2) {
      m2 = m;
      Serial.printf("%s water mark = %d\n", pcTaskGetTaskName(loop2TaskHandle),
                    m);
    }
  }
  m = esp_get_minimum_free_heap_size();
  if (m < mh) {
    mh = m;
    Serial.printf("free heap memory = %d\n", m);
  }
}

void setup() {
  esp_task_wdt_init(60, true);  // time in seconds
  enableLoopWDT();

  Serial.begin(115200);
  delay(100);

  // put your setup code here, to run once:
  Serial.println("Setup 1");
  printMemoryUse();
  createTask2();
  printMemoryUse();
}

void loop() {
  // put your main code here, to run repeatedly:
  printMemoryUse();
  Serial.println("loop 1");
  delay(1000);
}
