#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>

Sonar _sonar = Sonar(12,13);

void setup()
{
  _sonar.Setup();

  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  
}

void loop()
{
    _sonar.GetDistance();
}
