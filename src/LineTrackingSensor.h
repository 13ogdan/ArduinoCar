#include <Arduino.h>

class LineTrackingSensor
{
private:
  int _leftPin, _middlePin, _rightPin;
  int _left, _middle, _right;

public:
  enum Direction
  {
    Unknown,
    Forward,
    Left,
    Right,
  };

  LineTrackingSensor(int leftPin, int middlePin, int rightPin);
  ~LineTrackingSensor();
  void Setup();
  void LogState();
  LineTrackingSensor::Direction GetDirection();
};

LineTrackingSensor::LineTrackingSensor(int leftPin, int middlePin, int rightPin)
{
  _leftPin = leftPin;
  _middlePin = middlePin;
  _rightPin = rightPin;
}

LineTrackingSensor::~LineTrackingSensor()
{
}

void LineTrackingSensor::Setup()
{
  pinMode(_leftPin, INPUT);   // make the L_pin as an input
  pinMode(_middlePin, INPUT); // make the M_pin as an input
  pinMode(_rightPin, INPUT);  // make the R_pin as an input
}

void LineTrackingSensor::LogState()
{
  _left = digitalRead(_leftPin);
  _right = digitalRead(_rightPin);
  _middle = digitalRead(_middlePin);

  Serial.print("left:");
  Serial.print(_left);
  Serial.print(" middle:");
  Serial.print(_middle);
  Serial.print(" right:");
  Serial.println(_right);
}

LineTrackingSensor::Direction LineTrackingSensor::GetDirection()
{
  _left = digitalRead(_leftPin);
  _right = digitalRead(_rightPin);
  _middle = digitalRead(_middlePin);

  if (_left == 1 && _middle == 1 && _right == 1)
  {
    return Direction::Forward;
  }
  if (_left == 0 && _middle == 1 && _right == 0)
  {
    return Direction::Forward;
  }

  if (_left == 1 && _middle == 0 && _right == 0)
  {
    return Direction::Left;
  }
  if (_left == 1 && _middle == 1 && _right == 0)
  {
    return Direction::Left;
  }

  if (_left == 0 && _middle == 0 && _right == 1)
  {
    return Direction::Right;
  }
  if (_left == 0 && _middle == 1 && _right == 1)
  {
    return Direction::Right;
  }



  return Direction::Unknown;
}
