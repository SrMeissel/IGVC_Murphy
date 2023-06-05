
/*
  GY-271 Compass
  modified on 02 Sep 2020
  by Mohammad Reza Akbari @ Electropeak
  Home
*/

// I2C Library
#include <Wire.h>
// QMC5883L Compass Library
#include <QMC5883LCompass.h>

QMC5883LCompass compass;
int offset = -141;



void setup() {
  // Initialize the serial port.
  Serial.begin(9600);
  // Initialize I2C.
  Wire.begin();
  // Initialize the Compass.
  compass.init();
  //compass calibration
compass.setCalibration(-1403, 251, -868, 800, -1386, 0);

}

void loop() {
  int x, y, z;

  // Read compass values
  compass.read();

  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();

  Serial.print("X: ");
  Serial.print(x);
  Serial.print("   Y: ");
  Serial.print(y);
  Serial.print("   ");

  delay(300);

  float  heading = atan2(y, x);

  float declinationAngle = 0.663;
  heading += declinationAngle;

  //  * Convert the heading from radians to degrees for readability * /
  float headingDegrees = (heading * 180 / M_PI) + offset;

if (headingDegrees < -180) {
  headingDegrees = headingDegrees +360;
}

  Serial.print("Heaing (x): ");
  Serial.println(headingDegrees);






}
