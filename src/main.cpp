#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>
#include <LedBoard.h>


LedBoard _ledBoard(A5, A4);


void setup() {
  _ledBoard.Setup();
  Serial.begin(9600);
}
void loop() {
  for (int i = 0; i < 10; i++)
  {
    _ledBoard.Display((LedBoard::Image)i);
    delay(2000);
  }
  
}