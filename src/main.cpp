#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>
#include <LedBoard.h>
#include <Motor.h>


Motor _motor(2, 5, 4, 6);
Console* _console = new Console();


void setup() {
  _motor.Setup();
  Serial.begin(9600);
  Serial.println("Ready");
}
void loop() {
  String command = _console->ReadCommand();
  if (command != EMPTY)
  {
      int value = command.toInt();
      Serial.println(value);

      if (value >=0 && value <=4)
      {
        Serial.println("Move");
        _motor.Move((Motor::Direction)value);
      }else
      {
        Serial.println("Stop");
        _motor.Stop();
      }
  }
}