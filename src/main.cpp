#include <Arduino.h>

void setup()
{ 
  pinMode(9, OUTPUT);// initialize digital pin 9 as an output.
}

void loop() // the loop function runs over and over again forever
{ 
  for (int i = 0; i<255; i++)
  {
      analogWrite(9, i);
      delay(100);
  }
  
}
