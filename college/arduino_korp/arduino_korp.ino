#include "Arduino.h"
#include "ezBuzzer.h"
namespace {

};

class reaction_Game {
  public:
  

  private:
  int TopTime[3]{0, 0, 0};
  int milliseconds = 0;
  int level = 1;
  int delayTimes[3] = {400, 300, 250};
  const int buttonPins[5];
  const int ledPins[5];
  ezBuzzer piezo;


  



  public:
  reaction_Game(int yellow_LED_, int red_LED_, int blue_LED_, int green_LED_, int orange_LED_)
  : yellow_LED(yellow_LED_), red_LED(red_LED_), blue_LED(blue_LED_), green_LED(green_LED_), orange_LED(orange_LED_) {};
  void low_level(); 
  void medium_level();
  void hard_level();
  void set_level();
  void game_launch();
  
  int get_yellow_LED(const int& yellow_LED) const;
  int get_red_LED(const int& red_LED) const;
  int get_blue_LED(const int& blue_LED) const;
  int get_green_LED(const int& green_LED) const;
  int get_orange_LED(const int& orange_LED) const;

  public:
  virtual ~reaction_Game(){};


  private:
  void light_up_LED();
  void sound_reaction();
  void light_up_LEDS();
  void press_buttons();

};

//public
const int reaction_Game::get_yellow_LED( const int& yellow_LED) const { return *this; }
const int reaction_Game::get_red_LED( const int& red_LED) const { return *this; }
const int reaction_Game::get_blue_LED( const int& blue_LED) const { return *this; }
const int reaction_Game::get_green_LED(const int& green_LED) const { return *this; }
const int reaction_Game::get_orange_LED( const int& orange_LED) const { return *this; }

void reaction_Game::low_level() {level = 1; milliseconds = 400; }
void reaction_Game::medium_level() {level = 2; milliseconds = 300; }
void reaction_Game::hard_level() { level = 3; milliseconds = 250; }

void reaction_Game::set_level() {
  Serial.println("Enter game level (1 - low, 2 - medium, 3 - hard || yellow - 1, red - 2, blue - 3) ");

  for(int i = 0; i < 3; ++i) {
  digitalWrite(get_yellow_LED(), HIGH);
  delay(milliseconds);
  
  digitalWrite(get_red_LED(), HIGH);
  delay(milliseconds);
  
  digitalWrite(get_blue_LED(), HIGH);
  delay(milliseconds);
  
  digitalWrite(get_yellow_LED(), LOW);
  delay(milliseconds);
  
  digitalWrite(get_red_LED(), LOW);
  delay(milliseconds);
  
  digitalWrite(get_blue_LED(), LOW);
  delay(milliseconds);
  }


  unsigned long start_time = milliseconds();
  while(true) {
    if(Serial.available()) {
      int input = Serial.parseInt();
      if(input >= 1 && input <= 3) {
        switch(input) {
          case 1 : low_level(); return;
          case 2 : medium_level(); return;
          case 3 : hard_level(); return;
        }
      }
    }

    
    if(digitalRead(buttonPin_first)) {
      delay(milliseconds);
      low_level();
      return;
    }
    else if (digitalRead(buttonPin_second)) {
      delay(milliseconds);
      medium_level();
      return;
    }
    else if(digitalRead(buttonPin_third)) {
      delay(milliseconds);
      hard_level();
      return;
    }

    if(milliseconds - startTime > 10000) {
      Serial.println("Timeout, default choice - 1");
      low_level();
      return 0;
    }
  }
}
// end

//private

void reaction_Game::game_launch() {  
  Serial.println("Enter level for game: (1 - low; 2 - medium; 3 - hard) \n");
  while(!Serial.available());
  set_level();

  sound_reaction(); 
  light_up_LED();
};

void reaction_Game::light_up_LED() {
   int random_launch[5]{0, 0, 0, 0, 0}; 
   int button_enter[5] { buttonPin_first, buttonPin_second, buttonPin_third, buttonPin_fourth, buttonPin_fifth };
   
  for(int i = 1; i < 2; i++) {
    long randRes = random(5);
    random_launch[i] = randRes;
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
            
            if(res_counts < 3 || reactionTime < TopTime[2]) {
              if(res_counts < 3) {
                TopTime[res_counts] = reactionTime;
                res_counts++;
              } else {
                TopTime[2] = reactionTime;
              }
              
              for(int k = 1; k < res_counts; k++) {
                if(TopTime[k] < TopTime[k-1]) {
                  unsigned long temp = TopTime[k-1];
                  TopTime[k-1] = TopTime[k];
                  TopTime[k] = temp;
                }
              }
              
              Serial.println("Top result:");
              for(int k = 0; k < res_counts && k < 3; k++) {
                Serial.print(k+1);
                Serial.print(": ");
                Serial.print(TopTime[k]);
                Serial.println(" ms");
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

void reaction_Game::sound_reaction() {
  int ms = milliseconds;
  piezo.stop();
  piezo.beep(ms);
  delay(ms);
  piezo.stop();
}

void reaction_Game::light_up_LEDS() {
  
  for(int i = 1; i <= 3; i++) {  
  digitalWrite(get_yellow_LED(), HIGH);
  digitalWrite(get_red_LED(), HIGH);
  digitalWrite(get_blue_LED(), HIGH);
  digitalWrite(get_green_LED(), HIGH);
  digitalWrite(get_orange_LED(), HIGH);
  
  digitalWrite(get_yellow_LED(), LOW);
  digitalWrite(get_red_LED(), LOW);
  digitalWrite(get_blue_LED(), LOW);
  digitalWrite(get_green_LED(), LOW);
  digitalWrite(get_orange_LED(), LOW);
  }

}

void reaction_Game::press_buttons() {
int array_buttons[5]{buttonPin_first, buttonPin_second,
                    buttonPin_third, buttonPin_fourth,
                    buttonPin_fifth};
for (int i = 0; i < 4; ++i) {
  pinMode(array_buttons[i], INPUT);
}

}


void setup() {

}

void loop() {
  using::reaction_Game; 
  reaction_Game Game{};
  Game.game_launch();
  
  pinMode(get_yellow_LED(), OUTPUT);
  pinMode(get_red_LED(), OUTPUT);
  pinMode(get_blue_LED(), OUTPUT);
  pinMode(get_green_LED(), OUTPUT);
  pinMode(get_orange_LED(), OUTPUT);
  
  digitalWrite(get_yellow_LED(), LOW);
  digitalWrite(get_red_LED(), LOW);  
  digitalWrite(get_blue_LED(), LOW);
  digitalWrite(get_green_LED(), LOW); 
  digitalWrite(get_orange_LED(), LOW);
  
}
