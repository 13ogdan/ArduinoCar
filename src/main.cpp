#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>

Servo servo;
String command;
Console console;

boolean newData = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");

  servo.attach(A3);
  servo.write(90);

}

void loop()
{

}
