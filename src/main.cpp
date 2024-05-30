#include <Arduino.h>
#include <LineTrackingSensor.h>
#include <Servo.h>
#include <Console.h>
#include <Sonar.h>
#include <IRremote.h>
#include <LedBoard.h>
#include <Motor.h>

// Flags
bool _obstaclesAvoidMode = true;
bool _trackingSensorMode = false;
long _minDistance = 10;

Motor _motor(2, 5, 4, 6);
Sonar _sonar(12, 13);
Servo _servo;
LineTrackingSensor _lineTrackingSernsor(11, 7, 8);
LedBoard _ledBoard(A5, A4);

// Control
Console *_console = new Console();

// Methods
void Move(Motor::Direction newDirection);

void setup()
{
  _motor.Setup();
  _ledBoard.Setup();
  _sonar.Setup();
  _lineTrackingSernsor.Setup();

  _servo.attach(A3);
  _servo.write(90);

  Serial.begin(9600);
  Serial.println("Ready");

  _ledBoard.Display(LedBoard::Smile);
}
void loop()
{
  if (_obstaclesAvoidMode)
  {
    AvoidObstacle();
  }

  if (_trackingSensorMode)
  {
    FollowLine();
  }
}

void FollowLine()
{
  LineTrackingSensor::Direction lineDirection = _lineTrackingSernsor.GetDirection();
  switch (lineDirection)
  {
  case LineTrackingSensor::Left:
    Move(Motor::Direction::Left);
    break;
  case LineTrackingSensor::Right:
    Move(Motor::Direction::Right);
    break;
  case LineTrackingSensor::Forward:
    Move(Motor::Direction::Forward);
    break;
  case LineTrackingSensor::Unknown:
    Move(Motor::Direction::Forward);
    break;
  default:
    break;
  }
}

void AvoidObstacle()
{
  long distance = _sonar.GetDistance();
  if (distance < _minDistance)
  {
    _motor.Stop();
    _ledBoard.Display(LedBoard::Stop);

    _servo.write(0);
    long distanceToRight = _sonar.GetDistance();
    _servo.write(180);
    long distanceToLeft = _sonar.GetDistance();

    _servo.write(0);
    if (distanceToLeft > distanceToRight)
    {
      /// if both distance less then min - go back and repeat procedure
      while (distanceToLeft < _minDistance && distanceToRight < _minDistance)
      {
          Move(Motor::Direction::Back);
          delay(100);
          _servo.write(0);
          distanceToRight = _sonar.GetDistance();
         _servo.write(180);
          distanceToLeft = _sonar.GetDistance();
      }
      _motor.Stop();
      _ledBoard.Display(LedBoard::Stop);

      Motor::Direction newDirection = Motor::Direction::Right;
      if (distanceToLeft > distanceToRight)
      {
        newDirection = Motor::Direction::Left;
      }

      Move(newDirection);
      while (_sonar.GetDistance() < _minDistance)
      {
        delay(100);
      }
      Move(Motor::Direction::Forward);

      // TODO potentially need to be added looping period to reduce rotation speed
    }
  }
}

void Move(Motor::Direction newDirection)
{
  _motor.Move(newDirection);
  _ledBoard.Display((LedBoard::Image)newDirection);
}
