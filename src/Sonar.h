#include <Arduino.h>

class Sonar
{
private:
    int _trigPin, _echoPin;

public:
    Sonar(int trigPin, int echoPin);
    ~Sonar();
    void Setup();
    long GetDistance();
};

Sonar::Sonar(int trigPin, int echoPin)
{
    _trigPin = trigPin;
    _echoPin = echoPin;
}

Sonar::~Sonar()
{
}

inline void Sonar::Setup()
{
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

inline long Sonar::GetDistance()
{
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    long duration = pulseIn(_echoPin, HIGH);
    // Convert the time into a distance
    long cm = (duration / 2) / 29.1; // Divide by 29.1 or multiply by 0.0343
    return cm;
}
