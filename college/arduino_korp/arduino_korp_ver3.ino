#include <Arduino.h>
#include "ezBuzzer.h"
#include "EEPROM.h"

class reactionGame {
  private:
  const int buttonPin = 1;
  const int ledPins[5];

  int topTimes[3] = {0, 0, 0};
  int reactionTime = 0;
  int level = 1;
  int delayMs[3] = {400, 300, 250};
  int result_counts = 0;
  ezBuzzer piezo;


  void light_up_LEDS(int times) {
  for(int i = 0; i < times; i++) {
    for(int j = 0; j < 5; j++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(200);
    for(int k = 0; k < 5; k++) {
    digitalWrite(ledPins[j], LOW);
    }
    delay(200);
  }
}
};
