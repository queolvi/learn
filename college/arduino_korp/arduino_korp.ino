#include "Arduino.h"
#include "ezBuzzer.h"
#include "EEPROM.h"

class ReactionGame {
  private:
    const int buttonPins[5];
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
          digitalWrite(ledPins[j], HIGH);
        }
        delay(200);
        for(int j = 0; j < 5; j++) {
          digitalWrite(ledPins[j], LOW);
        }
        delay(200);
      }
    }
    
    void saveTopTimes() {
      for(int i = 0; i < 3; i++) {
        EEPROM.put(i * sizeof(int), topTimes[i]);
      }
    }
    
    void loadTopTimes() {
      for(int i = 0; i < 3; i++) {
        EEPROM.get(i * sizeof(int), topTimes[i]);
      }
    }
    
    int get_random_LED() { 
      return random(0, 5); 
    }
    
    bool check_button_press(int ledIndex) {
      unsigned long start_Time = millis();
      while(millis() - start_Time < delayMs[level - 1]) {
        if (digitalRead(buttonPins[ledIndex])) {
          reactionTime = millis() - start_Time;
          return true;
        }
      }
      return false;
    }

  public:
    ReactionGame(int* buttons, int* leds, int buzzerPin) :
      buttonPins{buttons[0], buttons[1], buttons[2], buttons[3], buttons[4]},
      ledPins{leds[0], leds[1], leds[2], leds[3], leds[4]},
      piezo(buzzerPin) {}

    void launch_game() {
      for(int i = 0; i < 5; i++) {
        pinMode(ledPins[i], OUTPUT);
        pinMode(buttonPins[i], INPUT);
      }
      loadTopTimes();
    }
    
    void setLevel(int newLevel) {
      if(newLevel >= 1 && newLevel <= 3) {
        level = newLevel;
        Serial.print("Level set to: ");
        Serial.println(level);
      }
    }
    
    void start_round() {
      int ledInx = get_random_LED();
      digitalWrite(ledPins[ledInx], HIGH);
      unsigned long startTime = millis();
      
      if(check_button_press(ledInx)) {
        digitalWrite(ledPins[ledInx], LOW);
        piezo.beep(100);

        if(result_counts < 3 || reactionTime < topTimes[2]) {
          if(result_counts < 3) {
            topTimes[result_counts] = reactionTime;
            result_counts++;
          } else {
            topTimes[2] = reactionTime;
          }
          
          for(int i = 1; i < result_counts; i++) {
            if(topTimes[i] < topTimes[i - 1]) {
              int temp = topTimes[i - 1];
              topTimes[i - 1] = topTimes[i];  
              topTimes[i] = temp;
            }
          }
          saveTopTimes();
        }
        
        Serial.print("Reaction time: ");
        Serial.print(reactionTime);
        Serial.println(" ms");
      } else {
        digitalWrite(ledPins[ledInx], LOW);
        light_up_LEDS(3);
        Serial.println("Too slow!");
      }
    }
    
    void showTopTimes() {
      Serial.println("Top results: ");
      for(int i = 0; i < 3; i++) {
        if(topTimes[i] > 0) {
          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(topTimes[i]);
          Serial.println(" ms");
        }
      }
    }
};

// Создаем экземпляр игры с конкретными пинами
int buttons[] = {2, 3, 4, 5, 6};
int leds[] = {7, 8, 9, 10, 11};
ReactionGame game(buttons, leds, 12);

void setup() {
  Serial.begin(9600);
  game.launch_game();
}

void loop() {
  Serial.println("Select level (1-3):");
  while(!Serial.available());
  int level = Serial.parseInt();
  game.setLevel(level);

  game.start_round();
  game.showTopTimes();
  delay(1000);
}