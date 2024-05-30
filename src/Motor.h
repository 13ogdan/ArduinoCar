#include <Arduino.h>

class Motor
{
private:
    int ML_Ctrl, ML_PWM, MR_Ctrl, MR_PWM;
    int MovingSpeed = 200;
    int RotationSpeed = 55;
public:
    Motor(int ML_Ctrl, int ML_PWM, int MR_Ctrl, int MR_PWM);
    ~Motor();

    enum Direction
    {
        Forward,
        Left,
        Right,
        Back
    };

    void Setup();

    void Move(Direction direction);
    void MoveLeft();
    void MoveRight();
    void MoveBack();
    void MoveForward();

    void IncreaseMovingSpeed(int increment);
    void IncreaseRotationSpeed(int increment);
    void Stop();
};

Motor::Motor(int ML_Ctrl, int ML_PWM, int MR_Ctrl, int MR_PWM)
{
    this->ML_Ctrl = ML_Ctrl;
    this->ML_PWM = ML_PWM;
    this->MR_Ctrl = MR_Ctrl;
    this->MR_PWM = MR_PWM;
}

Motor::~Motor()
{
}

inline void Motor::Setup()
{
    pinMode(ML_Ctrl, OUTPUT); // set direction control pins of group B motor to output
    pinMode(ML_PWM, OUTPUT);  // set PWM control pins of group B motor to output
    pinMode(MR_Ctrl, OUTPUT); // set direction control pins of group A motor to output
    pinMode(MR_PWM, OUTPUT);  // set PWM control pins of group A motor to output
}

inline void Motor::Move(Direction direction)
{
    Serial.print("Moving to:");
    Serial.println(direction);
    switch (direction)
    {
    case Direction::Left:
        MoveLeft();
        break;
    case Direction::Right:
        MoveRight();
        break;
    case Direction::Forward:
        MoveForward();
        break;
    case Direction::Back:
        MoveBack();
        break;
    default:
        break;
    }
}

inline void Motor::IncreaseMovingSpeed(int increment = 10)
{
    int prevValue = MovingSpeed;
    if (MovingSpeed + increment > 255)
        MovingSpeed = 255;
    else
        MovingSpeed = MovingSpeed + 10;

    if (prevValue != MovingSpeed)
    {
        Serial.print("Changed moving speed from-to:");
        Serial.print(prevValue);
        Serial.print("-");
        Serial.println(MovingSpeed);
    }
}

inline void Motor::IncreaseRotationSpeed(int increment = 10)
{
    int prevValue = RotationSpeed;
    if (RotationSpeed + increment > MovingSpeed)
        RotationSpeed = MovingSpeed - 10;
    else
        RotationSpeed = RotationSpeed + increment;

    if (prevValue != RotationSpeed)
    {
        Serial.print("Changed rotation speed from-to:");
        Serial.print(prevValue);
        Serial.print("-");
        Serial.println(RotationSpeed);
    }
}

inline void Motor::Stop()
{
    digitalWrite(ML_Ctrl, LOW); // set the direction control pins of group B motor to LOW level
    analogWrite(ML_PWM, 0);     // set the PWM control speed of group B motor to 0
    digitalWrite(MR_Ctrl, LOW); // set the direction control pins of group A motor to LOW level
    analogWrite(MR_PWM, 0);     // set the PWM control speed of group A motor to 0
}

inline void Motor::MoveLeft()
{
    digitalWrite(ML_Ctrl, LOW);  // set the direction control pins of group B motor to LOW level
    analogWrite(ML_PWM, MovingSpeed);    // set the PWM control speed of group B motor to 200
    digitalWrite(MR_Ctrl, HIGH); // set the direction control pins of group A motor to HIGH level
    analogWrite(MR_PWM, RotationSpeed);     // set the PWM control speed of group A motor to 200
}

inline void Motor::MoveRight()
{
    digitalWrite(ML_Ctrl, HIGH); // set the direction control pins of group B motor to HIGH level
    analogWrite(ML_PWM, RotationSpeed);     // set the PWM control speed of group B motor to 55
    digitalWrite(MR_Ctrl, LOW);  // set the direction control pins of group A motor to LOW level
    analogWrite(MR_PWM, MovingSpeed);    // set the PWM control speed of group A motor to 200
}

inline void Motor::MoveBack()
{
    digitalWrite(ML_Ctrl, LOW); // set the direction control pins of group B motor to LOW level
    analogWrite(ML_PWM, MovingSpeed);   // set the PWM control speed of group B motor to 200
    digitalWrite(MR_Ctrl, LOW); // set the direction control pins of group A motor to LOW level
    analogWrite(MR_PWM, MovingSpeed);   // set the PWM control speed of group A motor to 200
}

inline void Motor::MoveForward()
{
    digitalWrite(ML_Ctrl, HIGH); // set the direction control pins of group B motor to HIGH
    analogWrite(ML_PWM, MovingSpeed);     // set the PWM control speed of group B motor to 55
    digitalWrite(MR_Ctrl, HIGH); // set the direction control pins of group A motor to HIGH
    analogWrite(MR_PWM, MovingSpeed);     // set the PWM control speed of group A motor to 55
}
