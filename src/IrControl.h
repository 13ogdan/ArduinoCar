#include <IRremote.h>
#include <Arduino.h>

int RECV_PIN = 3;

enum Button
{
    Up,
    Left,
    Right,
    Down,
    Ok,
    Star,
    Sharp,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Num0,
    Error
};

struct Command
{
    bool IsReady;
    bool IsPressed;
    Button Button;
};

class IrControl
{
private:
    Button _lastButton;
    IRrecv *_reciver;
    decode_results results;

    Button IdentifyButton(unsigned long hexValue);

public:
    IrControl(int recPin);
    ~IrControl();
    void Setup();
    Command Read();
};

inline Button IrControl::IdentifyButton(unsigned long hexValue)
{
    switch (hexValue)
    {
    case 0xFF629D:
        return Button::Up;
    case 0xFF22DD:
        return Button::Left;
    case 0xFFC23D:
        return Button::Right;
    case 0xFFA857:
        return Button::Down;
    case 0xFF02FD:
        return Button::Ok;
    case 0xFF42BD:
        return Button::Star;
    case 0xFF52AD:
        return Button::Sharp;
    case 0xFF4AB5:
        return Button::Num0;
    case 0xFF6897:
        return Button::Num1;
    case 0xFF9867:
        return Button::Num2;
    case 0xFFB04F:
        return Button::Num3;
    case 0xFF30CF:
        return Button::Num4;
    case 0xFF18E7:
        return Button::Num5;
    case 0xFF7A85:
        return Button::Num6;
    case 0xFF10EF:
        return Button::Num7;
    case 0xFF38C7:
        return Button::Num8;
    case 0xFF5AA5:
        return Button::Num9;
    default:
        return Button::Error;
    }
    return Button();
}

IrControl::IrControl(int recPin)
{
    _reciver = new IRrecv(recPin);
}

IrControl::~IrControl()
{
}

inline void IrControl::Setup()
{
    _reciver->enableIRIn();
}

inline Command IrControl::Read()
{
    Command result;
    result.IsReady = false;
    result.IsPressed = false;

    if (_reciver->decode(&results)) // decode successfully, receive a set of infrared signals
    {
        Serial.println(results.value, HEX); // Wrap word in 16 HEX to output and receive code

        result.IsReady = true;
        if (results.value == 0xFFFFFFFF)
        {
            result.IsPressed = true;
            result.Button = _lastButton;
        }
        else
        {
            _lastButton = IdentifyButton(results.value);
            result.Button = _lastButton;
        }

        _reciver->resume(); // Receive the next value
    }
    return result;
}
