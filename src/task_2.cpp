#include <Arduino.h>

#include "task_manager.h"

void setup2(void) {
  enableLoop2WDT();

  // put your setup code here, to run once:
  Serial.println("Setup 2");
}

void loop2(void) {
  // put your main code here, to run repeatedly:

  Serial.println("loop 2");
  delay(3000);
}
