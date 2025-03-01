#define BAUD_RATE 2000000
// Serial initialization timeout (in ms)
#define SERIAL_TIMEOUT 1000
// Infrared communication
#define IR_SEND_PIN 2
// Ambient light color pins
#define AL_RED_PIN 3
#define AL_GREEN_PIN 6
#define AL_BLUE_PIN 9
#define AL_MAX_VALUE 220
// Response codes
#define RESCODE_SUCCESS 200
#define RESCODE_UNKNOWN 44
// Modules and libraries
#include "Arduino.h"
#include "Mainlight.hpp"


bool isValid = false;

void manageMainlightInput(char receivedKey) {
  MainlightAction cmd;
  if (Mainlight::tryGetAction(receivedKey, &cmd)) {
    byte code = Mainlight::sendAction(cmd);
    Serial.println(code);
  }
}

void setup() {
  // Output pins for analog 5050 RGB LED strip
  pinMode(AL_RED_PIN, OUTPUT);
  pinMode(AL_GREEN_PIN, OUTPUT);
  pinMode(AL_BLUE_PIN, OUTPUT);

  // Serial initialization
  int passed = 0;
  Serial.begin(BAUD_RATE);
  while (!Serial && passed < SERIAL_TIMEOUT)
  {
    delay(1);
    passed += 1;
  }
  isValid = Serial;
}
void loop() {
  if (Serial.available()) {
    char receivedKey = Serial.read();
    
    manageMainlightInput(receivedKey);
  }
}