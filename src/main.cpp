#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>

#define DEBUG
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

String Serialdata = "";
bool dataflag = 0;
long timestamp = 0;

void setup()
{
  Serial.begin(250000); // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin(9600); // Change this baudrate as per your bluetooth baudrate. Connect bluetooth on digital pin 2(RX) and 3(TX) for Uno/Nano and on Serial3 pins for Mega.
}

void loop()
{
  Dabble.processInput();
  long newTimestamp = millis();
  if (newTimestamp - timestamp > 2000)
  {
    
    timestamp = newTimestamp;
    String value = "";

    value = "Is initialized: " +  String(Dabble.isInitialized());
    value += "\t isAppConnected:" + String(Dabble.isAppConnected());
    value += "\t isSoftwareSerial:" + String(Dabble.isSoftwareSerial());
    value += "\t DabbleSerial:" + String(Dabble.DabbleSerial->available());
    
    Serial.println(value);
  }

  while (Serial.available())
  {
    int newChar = Serial.read();
    Terminal.write(newChar);
  }

  while (Terminal.available())
  {
    int newChar = Terminal.read();
    Serial.write(newChar);
  }
  
}