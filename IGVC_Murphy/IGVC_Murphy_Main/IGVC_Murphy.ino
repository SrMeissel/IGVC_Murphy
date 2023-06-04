#include "SR04.h"

//Define Variables
#define TRIG_PIN_Right 11
#define ECHO_PIN_Right 10
#define TRIG_PIN_Mid 12
#define ECHO_PIN_Mid 13
#define TRIG_PIN_Left 2
#define ECHO_PIN_Left 3
int tooClose = 15;

//Setup Echo and Trig Pins
SR04 sr04 = SR04(ECHO_PIN_Right, TRIG_PIN_Right);
SR04 sr05 = SR04(ECHO_PIN_Mid, TRIG_PIN_Mid);
SR04 sr06 = SR04(ECHO_PIN_Left, TRIG_PIN_Left);
long a;
long b;
long c;

void setup() {
  Serial.begin(9600);//Initialization of Serial Port
  delay(1000);
}

void loop() {
Obstacle_detection ();

}


void Obstacle_detection (){

  //Define distances
  a = sr04.Distance();
  b = sr05.Distance();
  c = sr06.Distance();

  delay(1000);

//if statement to determine what 
  if (a < tooClose) {
    Serial.println("distance_left");
    Serial.print(a);
    Serial.println("cm");//The difference between "Serial.print" and "Serial.println"
    //is that "Serial.println" can change lines.
  } else if (b < tooClose) {
    Serial.println("distance_mid");
    Serial.print(b);
    Serial.println("cm");//The difference between "Serial.print" and "Serial.println"
    //is that "Serial.println" can change lines.
  } else if (c < tooClose) {
    Serial.println("distance_right");
    Serial.print(c);
    Serial.println("cm");//The difference between "Serial.print" and "Serial.println"
    //is that "Serial.println" can change lines.
  }
}
