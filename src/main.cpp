#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IrControl.h>

IrControl _irControl(3);

void setup()
{
  _irControl.Setup();
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop()
{
  Command command = _irControl.Read();
  if (command.IsReady) // decode successfully, receive a set of infrared signals
  {
    Serial.print("New command: is pressed=");
    Serial.print(command.IsPressed);
    Serial.print(" value=");
    Serial.println(command.Button);
  }
}