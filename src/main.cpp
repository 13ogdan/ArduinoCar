#include <Arduino.h>
#include <LineTrackingSensor.h>

LineTrackingSensor *_lineTrackingSensor;
LineTrackingSensor::Direction _lastDirection = LineTrackingSensor::Direction::Unknown;

void setup()
{
  _lineTrackingSensor = new LineTrackingSensor(11, 7, 8);
  _lineTrackingSensor->Setup();

  pinMode(9, OUTPUT); // initialize digital pin 9 as an output.

  Serial.begin(9600);
}

void loop() // the loop function runs over and over again forever
{
  LineTrackingSensor::Direction direction = _lineTrackingSensor->GetDirection();
  if (direction != _lastDirection)
  {
    _lastDirection = direction;
    LogDirection();
  }
}

void LogDirection()
{
  switch (_lastDirection)
  {
  case LineTrackingSensor::Direction::Left:
    Serial.println("Left");
    break;
  case LineTrackingSensor::Direction::Right:
    Serial.println("Right");
    break;
  case LineTrackingSensor::Direction::Forward:
    Serial.println("Forward");
    break;
  case LineTrackingSensor::Direction::Unknown:
    Serial.println("Unknown");
    break;

  default:
    Serial.println("ERROR");
  }
}
