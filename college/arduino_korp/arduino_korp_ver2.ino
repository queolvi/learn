#include "Arduino.h"
#include "ezBuzzer.h"
#include "EEPROM.h"

class reactionGame {
  private:
  const int buttonPins[5];
  const int ledPins[5];

  int topTimes[3] = {0, 0, 0};
  int reactionTime = 0;
  int level = 1;
  int delayMs[3] = {400, 300, 250};
  int result_counts = 0;
  ezBuzzer piezo;

  void light_up_LEDS(int times);
  void saveTopTimes();
  void loadTopTimes();
  int get_random_LED();
  bool check_button_press(int ledIndex);

  public:
  reactionGame(int* buttons, int* leds, int buzzerPin) :
  buttonPins{buttons[0], buttons[1],buttons[2], buttons[3], buttons[4]},
  ledPins{leds[0], leds[1], leds[2], leds[3], leds[4]},
  piezo(buzzerPin) {};

  void launch_game();
  void setLevel(int newLevel);
  void start_round();
  void showTopTimes();
};

void setup() {
  Serial.begin(9600);
  game.launch_game();
}

void loop() {
  Serial.println("Choose difficulty level (1 - 3): ");
  while(!Serial.available());
  int level = Serial.parseInt();
  game.setLevel(level);

  game.(start_round);
  game.showTopTimes();

  delay(1000);
}

// public-methods
void reactionGame::light_up_LEDS(int times) {
  for(int i = 0; i < times; i++) {
    for(int j = 0; j < 5; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(200);
    for(int j = 0; j < 5; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(200);
  }
}

void reactionGame::saveTopTimes() {
  for(int i = 0; i < 3; i++) {
    EEPROM.put(i * sizeof(int). topTimes[i]);
  }
}

void reactionGame::loadTopTimes() {
  for(int i = 0; i < 3; i++) {
    EEPROM.get(i * sizeof(int), topTimes[i]);
  }
}

int reactionGame::get_random_LED() { int res = random(0, 5); return res; }

bool reactionGame::check_button_press(int ledIndex) {
  unsigned long start_Time = millis();
  while(millis() - start_Time < delayMs[level - 1]) {
    if (digitalRead(buttonPins[ledIndex])) {
      reactionTime = millis() - start_Time;
      return true;
    }
  }
  return false;
}

//private-methods
void reactionGame::launch_game() {
  for(int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], OUTPUT);
  }
  loadTopTimes();
}

void reactionGame::setLevel(int newLevel) {
  if(newLevel >= 1 && newLevel <= 3) {

  }
}
void reactionGame::start_round();
void reactionGame::showTopTimes();



