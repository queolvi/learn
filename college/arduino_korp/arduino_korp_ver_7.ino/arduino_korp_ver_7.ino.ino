#include "Arduino.h"
#include "ezBuzzer.h"
#include "EEPROM.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

class ReactionGame {
  private:
    const int buttonPin;
    const int* ledPins;
    int topTimes[3][3]; 
    int reactionTime = 0;
    int level = 1;
    int delayMs[3] = {400, 300, 250};
    int result_counts = 0;
    int currentUser = 0; 
    ezBuzzer piezo;

    void light_up_LEDS(int times);
    void saveTopTimes();
    void loadTopTimes();
    int get_random_LED();
    bool check_button_press();
    
  public:
    void displayMessage(const String& msg);
    int any_choice_with_button(int* options, int optionsCount);
    ReactionGame(int button, const int leds[], int buzzerPin);
    void launch_game();
    void selectUser();
    void setLevel();
    void start_round();
    void showTopTimes();
    ~ReactionGame();
};

///////////////////////////////////////////////////////////////////////////////////
//  REACTION_GAME_CLASS_IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////

ReactionGame::ReactionGame(int button, const int leds[], int buzzerPin) : 
  buttonPin(button),
  ledPins(leds),
  piezo(buzzerPin) {
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        topTimes[i][j] = 0;
      }
    }
}

void ReactionGame::displayMessage(const String& msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
  Serial.println(msg);
}


int ReactionGame::any_choice_with_button(int* options, int optionsCount) {
    int currentOption = 0;
    unsigned long lastChangeTime = 0;
    const int cycleDelay = 500;

    while(true) {
      unsigned long currentTime = millis();
      if(currentTime - lastChangeTime > cycleDelay) {
        for(int i = 0; i < optionsCount; i++) {
          digitalWrite(ledPins[options[i]], i == currentOption ? HIGH : LOW);
        }
        lastChangeTime = currentTime;
        currentOption = (currentOption + 1) % optionsCount;
      }
      if(digitalRead(buttonPin)) {
        delay(50);
        while(digitalRead(buttonPin));
        return options[currentOption];
      }
    }
}

void ReactionGame::light_up_LEDS(int times) {
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

void ReactionGame::saveTopTimes() {
  int address = currentUser * 3 * sizeof(int); 
  for(int i = 0; i < 3; i++) {
    EEPROM.put(address + i * sizeof(int), topTimes[currentUser][i]);
  }
} 

void ReactionGame::loadTopTimes() {
  int address = currentUser * 3 * sizeof(int); 
  for(int i = 0; i < 3; i++) {
    EEPROM.get(address + i * sizeof(int), topTimes[currentUser][i]);
  }
}

int ReactionGame::get_random_LED() {
  return random(0, 5);
}

bool ReactionGame::check_button_press() {
  unsigned long start_Time = millis();
  while(millis() - start_Time < delayMs[level - 1]) {
    if(digitalRead(buttonPin)) {
      reactionTime = millis() - start_Time;
      return true;
    }
  }
  return false;
}

void ReactionGame::launch_game() {
  pinMode(buttonPin, INPUT_PULLUP);
  for(int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  selectUser(); 
  loadTopTimes();
}

void ReactionGame::selectUser() {
  int users[] = {0, 1, 2}; 
  currentUser = any_choice_with_button(users, 3);
  String msg = "User: " + String(currentUser + 1);
  displayMessage(msg);
}

void ReactionGame::setLevel() {
  int levels[] = {0, 1, 2};
  level = any_choice_with_button(levels, 3) + 1;
  String msg = "Level: " + String(level);
  displayMessage(msg);
}

void ReactionGame::start_round() {
  int ledInx = get_random_LED();
  digitalWrite(ledPins[ledInx], HIGH);
  unsigned long startTime = millis();
  
  if(check_button_press()) {
    digitalWrite(ledPins[ledInx], LOW);
    piezo.beep(100);

    if(result_counts < 3 || reactionTime < topTimes[currentUser][2]) {
      if(result_counts < 3) {
        topTimes[currentUser][result_counts] = reactionTime;
        result_counts++;
      } else {
        topTimes[currentUser][2] = reactionTime;
      }
      
      for(int i = 1; i < result_counts; i++) {
        if(topTimes[currentUser][i] < topTimes[currentUser][i - 1]) {
          int temp = topTimes[currentUser][i - 1];
          topTimes[currentUser][i - 1] = topTimes[currentUser][i];  
          topTimes[currentUser][i] = temp;
        }
      }
      saveTopTimes();
    }
    
    String msg = "Time: " + String(reactionTime) + " ms";
    displayMessage(msg);
  } else {
    digitalWrite(ledPins[ledInx], LOW);
    light_up_LEDS(3);
    displayMessage("Too slow!");
  }
}

void ReactionGame::showTopTimes() {
  String msg = "Top for User " + String(currentUser + 1) + ":\n";
  for(int i = 0; i < 3; i++) {
    if(topTimes[currentUser][i] > 0) {
      msg += String(i + 1) + ": " + String(topTimes[currentUser][i]) + " ms\n";
    }
  }
  displayMessage(msg);
}

///////////////////////////////////////////////////////////////////////////////////
//  MAIN PROGRAM
///////////////////////////////////////////////////////////////////////////////////

int leds[] = {7, 8, 9, 10, 11};
ReactionGame game(2, leds, 12);

void setup() {
  Serial.begin(9600);
  
  // Инициализация OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  game.launch_game();
}

void loop() {
  game.displayMessage("Select level:"); 
  game.setLevel();

  game.start_round();
  game.showTopTimes();
  delay(1000);
  
  game.displayMessage("Press to change user");
  while(!digitalRead(2)); 
  delay(200);
  game.selectUser();
}