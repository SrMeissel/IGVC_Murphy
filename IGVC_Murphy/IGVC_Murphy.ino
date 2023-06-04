#include "SR04.h"
#include <FastLED.h>

//Define Variables
#define TRIG_PIN_Right 11
#define ECHO_PIN_Right 10
#define TRIG_PIN_Mid 12
#define ECHO_PIN_Mid 13
#define TRIG_PIN_Left 2
#define ECHO_PIN_Left 3
#define LED_PIN 4
#define NUM_LEDS 60
#define ESTOP_PIN 5

int tooClose = 15;
int ID = 0;
CRGB leds[NUM_LEDS];

//Setup Echo and Trig Pins
SR04 sr04 = SR04(ECHO_PIN_Right, TRIG_PIN_Right);
SR04 sr05 = SR04(ECHO_PIN_Mid, TRIG_PIN_Mid);
SR04 sr06 = SR04(ECHO_PIN_Left, TRIG_PIN_Left);
long a;
long b;
long c;

String currentMode = "";
String newMode = "";

void setup() {
  Serial.begin(9600);//Initialization of Serial Port
  delay(1000);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(ESTOP_PIN, OUTPUT); 
}

void loop() {
  Obstacle_detection();
  readSerialPort();

  if (newMode != currentMode) {
      // Update the current mode and perform corresponding actions
    currentMode = newMode;

      // Switch-case based on the current mode
    switchMode(currentMode);
    
  }

  // Continue performing actions for the current mode
  switchMode(currentMode);

  

  delay(1000); // Delay for 1 second
}


void Obstacle_detection(){

  //Define distances
  a = sr04.Distance();
  b = sr05.Distance();
  c = sr06.Distance();

  delay(1000);

//if statement to determine what 
  if (a < tooClose || b < tooClose || c < tooClose) { //this might cause problems;
    
    sendData();
  
  }
}

void sendData() {
  //write data ledState x sensor1 x sensor2
  Serial.println(ID);
  Serial.print(",");
  Serial.print(a);
  Serial.print(",");
  Serial.print(b);
  Serial.print(",");
  Serial.print(c);
    
  ID = ID++;
}

void LEDOff(){
  leds[59] = CRGB(0, 0, 0);
  FastLED.show();

}

void blinkColor(){

  for (int i = 0; i <= 59; i++) {
    leds[i] = CRGB(0, 255, 0);
    delay(10);
  }
  FastLED.show();

  for (int i = 59; i >= 0; i--) {
    leds[i] = CRGB(0, 0, 0);
    delay(10);
  }
  FastLED.show();
}

void solidRed(){
  
  leds[59] = CRGB(255, 0, 0);
  FastLED.show();

}

void solidGreen(){
  
  leds[59] = CRGB(0, 255, 0);
  FastLED.show();

}

void solidBlue(){
  
  leds[59] = CRGB(0, 0, 255);
  FastLED.show();

}

void readSerialPort() {
  //String msg = "";
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n'); // Read the incoming message

    // Find the position of the commas in the message
    int firstComma = message.indexOf(',');

    // Extract the string and integer values from the message
    int ID = message.substring(0, firstComma).toInt();//message ID
    String newMode = message.substring(firstComma + 1);

    
    
    
    
  }
}

void switchMode(const String& currentMode) {
  // Switch-case based on the mode
  if (currentMode == "autonomous") {
    digitalWrite(ESTOP_PIN, HIGH);
    blinkColor();
    Obstacle_detection();
  } 
  else if (currentMode == "manual") {
    digitalWrite(ESTOP_PIN, HIGH);
    // Add code for manual mode
    solidGreen();
  } 
  else if (currentMode == "Estopped") {
    digitalWrite(ESTOP_PIN, LOW); 
    // Add code for stopped mode
    solidRed();
  } 
  else if (currentMode == "debug") {
    digitalWrite(ESTOP_PIN, HIGH);
    LEDOff();
    Obstacle_detection();
    if (a < tooClose){
      for (int i = 0; i <= 19; i++) {
        leds[i] = CRGB(0, 255, 0);
        delay(10);
      }
      FastLED.show();

    }

    if (b < tooClose){
      for (int i = 20; i <= 39; i++) {
        leds[i] = CRGB(0, 255, 0);
        delay(10);
      }
      FastLED.show();

    }

    if (c < tooClose){
      for (int i = 40; i <= 59; i++) {
        leds[i] = CRGB(0, 255, 0);
        delay(10);
      }
      FastLED.show();

    }
    
    
  } 
  else {
    
    // Add code for handling invalid mode
  }
}


