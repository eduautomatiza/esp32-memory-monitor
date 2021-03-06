# esp32-memory-monitor 

Example of memory monitor, freeRTOS, for ESP32 running two tasks. 


The project uses [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode), [Visual Studio Code](https://code.visualstudio.com/) and [arduino framework for espressif32 platform](https://github.com/espressif/arduino-esp32);

**the function printMemoryUse():**
```C++
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
```

**first task, main.cpp:**
```C++
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
```


**second task, task_2.cpp:**
```C++
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
```


**Serial terminal output:**
```
Setup 1
loopTask water mark = 7524
free heap memory = 283380
Setup 2
loop 2
loopTask water mark = 6744
task2 water mark = 7652
free heap memory = 274772
loop 1
loop 1
loop 1
loop 2
loop 1
loop 1
loop 1
loop 2
loop 1
loop 1
loop 1
loop 2
loop 1
loop 1
loop 1
loop 2
loop 1
loop 1
loop 1
loop 2
loop 1
loop 1
```
