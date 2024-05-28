#include <Arduino.h>

void setup()
{ 
  pinMode(9, OUTPUT);// initialize digital pin 9 as an output.
}

void loop() // the loop function runs over and over again forever
{ 
  for (int light = 0; light<255; light=light+1)
  {
      analogWrite(9, light);
      delay(10);
  }
  
  for (int light = 255; light>0; light=light-1)
  {
      analogWrite(9, light);
      delay(10);
  }
}
