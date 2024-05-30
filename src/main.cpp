#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>


int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);   
decode_results results;

void setup()
{
  irrecv.enableIRIn(); 
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop()
{
   if (irrecv.decode(&results))//decode successfully, receive a set of infrared signals  
   {  
     Serial.println(results.value, HEX);//Wrap word in 16 HEX to output and receive code 
     irrecv.resume(); // Receive the next value
   }  
   delay(100);  
}