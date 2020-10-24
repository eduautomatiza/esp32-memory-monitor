# esp32-task-example

Example for Arduino using ESP32 and running two tasks and enabling the watchdog timer.


The project uses [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode), [Visual Studio Code](https://code.visualstudio.com/) and [arduino framework for espressif32 platform](https://github.com/espressif/arduino-esp32);


**first task, main.cpp:**
```C++
void setup() {

  esp_task_wdt_init(60, true); // time in seconds
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
Setup 2
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
```
