#include <Arduino.h>

void setup()
{ 
  pinMode(9, OUTPUT);// initialize digital pin 9 as an output.

  Serial.print("Hello, World!\r\nArduino Forever");
}

void loop() // the loop function runs over and over again forever
{ 
  Serial.begin(9600);

  Serial.println("turn the LED on (HIGH is the voltage level)");
  digitalWrite(9, HIGH); // turn the LED on (HIGH is the voltage level)
  
  Serial.println("wait for a second");
  delay(3000); // wait for a second

  Serial.println("turn the LED off by making the voltage LOW");
  digitalWrite(9, LOW); // turn the LED off by making the voltage LOW
  
  Serial.println("wait for a second");
  delay(1000); // wait for a second

  Serial.end();
}
