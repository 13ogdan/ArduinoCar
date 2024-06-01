#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>

Console* console = new Console();

void setup()
{
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  console->SetCommandEnding(";");
}

void loop()
{
  String command = console -> ReadCommand();
  if (command != EMPTY)
  {
    Serial.println("New command: " + command);
    if (command == "путін")
        Serial.println("=Хуйло");
  }
   delay(100);  
}