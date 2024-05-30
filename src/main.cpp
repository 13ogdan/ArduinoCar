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
  console = Console();

  servo.attach(A3, 0000, 2500);
  servo.write(0);

}

void loop()
{
  String command = console.ReadCommand();
  if (command != EMPTY)
  {
    int angle = command.toInt();
    Serial.print("Send angle:");
    Serial.println(angle);
    servo.write(angle);
  }
}
