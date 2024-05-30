#include <Arduino.h>

class LedBoard
{
private:
    int _SCL_Pin, _SDA_Pin;

public:
    enum Image
    {
        Forward,
        Left,
        Right,
        Back,
        Start,
        Stop,
        Clear,
        Smile,
        Error,
    };

    LedBoard(int SCL_Pin, int SDA_Pin);
    ~LedBoard();
    void Setup();
    void Display(Image image);

private:
    void matrix_display(unsigned char matrix_value[]);
    void IIC_start();
    void IIC_end();
    void IIC_send(unsigned char send_data);
};

unsigned char _start[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
unsigned char _front[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x12, 0x09, 0x12, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char _back[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x48, 0x90, 0x48, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char _left[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x44, 0x28, 0x10, 0x44, 0x28, 0x10, 0x00};
unsigned char _right[] = {0x00, 0x10, 0x28, 0x44, 0x10, 0x28, 0x44, 0x10, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char _stop[] = {0x2E, 0x2A, 0x3A, 0x00, 0x02, 0x3E, 0x02, 0x00, 0x3E, 0x22, 0x3E, 0x00, 0x3E, 0x0A, 0x0E, 0x00};
unsigned char _clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char _error[] = {0x00, 0x80, 0xc0, 0x68, 0x24, 0x24, 0x28, 0x20, 0x20, 0x28, 0x24, 0x24, 0x68, 0xc0, 0x80, 0x00};
unsigned char _smile[] = {0x00, 0x00, 0x00, 0x10, 0x20, 0x40, 0x4e, 0x40, 0x40, 0x40, 0x4e, 0x40, 0x20, 0x10, 0x00, 0x00};

LedBoard::LedBoard(int SCL_Pin, int SDA_Pin)
{
    _SCL_Pin = SCL_Pin;
    _SDA_Pin = SDA_Pin;
}

LedBoard::~LedBoard()
{
}

inline void LedBoard::Setup()
{
    pinMode(_SCL_Pin, OUTPUT);
    pinMode(_SDA_Pin, OUTPUT);
}

inline void LedBoard::Display(Image image)
{
    switch (image)
    {
    case Image::Start:
        matrix_display(_start);
        break;
    case Image::Stop:
        matrix_display(_stop);
        break;
    case Image::Left:
        matrix_display(_left);
        break;
    case Image::Right:
        matrix_display(_right);
        break;
    case Image::Forward:
        matrix_display(_front);
        break;
    case Image::Back:
        matrix_display(_back);
        break;
    case Image::Clear:
        matrix_display(_clear);
        break;
    case Image::Smile:
        matrix_display(_smile);
        break;
    case Image::Error:
        matrix_display(_error);
        break;
    default:
        matrix_display(_error);
        break;
    }
}

// this function is used for dot matrix display
inline void LedBoard::matrix_display(unsigned char matrix_value[])
{
    IIC_start();    // the function that calls the data transfer start condition
    IIC_send(0xc0); // select address

    for (int i = 0; i < 16; i++) // the pattern data is 16 bytes
    {
        IIC_send(matrix_value[i]); // Transmit the data of the pattern
    }
    IIC_end(); // End pattern data transmission
    IIC_start();
    IIC_send(0x8A); // Display control, select 4/16 pulse width
    IIC_end();
}

// Conditions under which data transmission begins
inline void LedBoard::IIC_start()
{
    digitalWrite(_SDA_Pin, HIGH);
    digitalWrite(_SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(_SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(_SCL_Pin, LOW);
}

// Indicates the end of data transmission
inline void LedBoard::IIC_end()
{
    digitalWrite(_SCL_Pin, LOW);
    digitalWrite(_SDA_Pin, LOW);
    delayMicroseconds(3);
    digitalWrite(_SCL_Pin, HIGH);
    delayMicroseconds(3);
    digitalWrite(_SDA_Pin, HIGH);
    delayMicroseconds(3);
}

// transmit data
inline void LedBoard::IIC_send(unsigned char send_data)
{
    for (byte mask = 0x01; mask != 0; mask <<= 1) // Each byte has 8 bits and is checked bit by bit starting at the lowest level
    {
        if (send_data & mask)
        { // Sets the high and low levels of SDA_Pin depending on whether each bit of the byte is a 1 or a 0
            digitalWrite(_SDA_Pin, HIGH);
        }
        else
        {
            digitalWrite(_SDA_Pin, LOW);
        }
        delayMicroseconds(3);
        digitalWrite(_SCL_Pin, HIGH); // Pull the clock pin SCL_Pin high to stop data transmission
        delayMicroseconds(3);
        digitalWrite(_SCL_Pin, LOW); // pull the clock pin SCL_Pin low to change the SIGNAL of SDA
    }
}