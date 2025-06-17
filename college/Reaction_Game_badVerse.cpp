#include "Arduino.h"
#include <iostream>
class user {};
class game {};
int TopTime[3]{0, 0, 0};
int res_counts = 0;
short level = 0;
short milliseconds = 0;
const int yellow_LED = 0, red_LED = 0,
blue_LED = 0, green_LED = 0, orange_LED = 0;

const int buttonPin_first = 0, buttonPin_second = 0,
buttonPin_third = 0, buttonPin_fourth = 0,
buttonPin_fifth = 0;



void game_launch() {

  
  Serial.println("Enter level for game: (1 - low; 2 - medium; 3 - hard) \n");
  while(!Serial.available());
  level = Serial.parseInt();

  if(level == 1) {
    low_level();
  } else if (level == 2) {
    medium_level();
  } else if (level == 3) {
    hard_level();
  }
   
  light_up_LED();
  

};
void low_level() { milliseconds = 400; }
void medium_level() { milliseconds = 300; }
void hard_level() { milliseconds = 250; }

void light_up_LED() {
  auto random_launch[4]{ yellow_LED, red_LED, blue_LED, green_LED, orange_LED};
  auto button_enter[4]{ buttonPin_first, buttonPin_second, buttonPin_third, buttonPin_fourth, buttonPin_fifth; }
   
  for(int i = 0; i < 1; ++i) {
    random_launch[i] = rand(5);
    digitalWrite(random_launch[i], HIGH);
    unsigned long startTime = millis();
    delay(milliseconds);
    digitalWrite(random_launch[i], LOW);
    
    for(int j = 0; j < 5; ++j) {
      if(button_enter[j] == random_launch[i]){
        unsigned long buttonPressTime = 0;
        unsigned long waitStart = millis();
        
        while(millis() - waitStart < milliseconds) {
          if(digitalRead(button_enter[j])) {
            buttonPressTime = millis();
            unsigned long reactionTime = buttonPressTime - startTime;
            
            if(resultsCount < 3 || reactionTime < bestTimes[2]) {
              if(resultsCount < 3) {
                TopTime[resultsCount] = reactionTime;
                resultsCount++;
              } else {
                TopTime[2] = reactionTime;
              }
              
              for(int k = 1; k < resultsCount; k++) {
                if(TopTime[k] < TopTime[k-1]) {
                  unsigned long temp = TopTime[k-1];
                  TopTime[k-1] = TopTime[k];
                  TopTime[k] = temp;
                }
              }
              
              Serial.println("Top result:");
              for(int k = 0; k < resultsCount && k < 3; k++) {
                Serial.print(k+1);
                Serial.print(": ");
                Serial.print(TopTime[k]);
                Serial.println(" мс");
              }
            }
            
            break;
          }
        }
        
        delay(milliseconds);
      } 
    }
}

}

void sound_reaction() {

}
void dump_time() {

}
void light_up_LEDS() {
  digitalWrite(yellow_LED, HIGH);
  digitalWrite(red_LED, HIGH);
  digitalWrite(blue_LED, HIGH);
  digitalWrite(green_LED, HIGH);
  digitalWrite(orange_LED, HIGH);

  digitalWrite(yellow_LED, LOW);
  digitalWrite(red_LED, LOW);
  digitalWrite(blue_LED, LOW);
  digitalWrite(green_LED, LOW);
  digitalWrite(orange_LED, LOW);
}
void count_points() {

}
void dump_record() {

}




void setup() {}
void loop() {
  game_launch();
  
  pinMode(yellow_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(orange_LED, OUTPUT);
  
  digitalWrite(yellow_LED, LOW);
  digitalWrite(red_LED, LOW);  
  digitalWrite(blue_LED, LOW);
  digitalWrite(green_LED, LOW); 
  digitalWrite(orange_LED, LOW);
  





}
// https://github.com/tsmith165/nvchad-ubuntu-installer
