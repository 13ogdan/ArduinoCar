#include <Arduino.h>

static const String EMPTY = "";

class Console
{
private:
    String _buffer = String();
    boolean _readingInProggress = false;
    String _endLine = "\r\n";
    String _endMarker = "\r\n";

public:
    Console();
    String ReadCommand();
    void SetCommandEnding(String newEndMarker);
};

Console::Console()
{
}

String Console::ReadCommand()
{
    String receivedChars;
    if (Serial.available() <= 0)
        return EMPTY;

    receivedChars = Serial.readString();
    if (receivedChars == NULL || receivedChars.length() == 0)
        return EMPTY;

    _buffer += receivedChars;
    int separatorIndex = _buffer.indexOf(_endMarker);
    if (separatorIndex < 0)
        return EMPTY;

    // Serial.print("Index:");
    // Serial.println(separatorIndex);
    // Serial.println("Buffer before:" + _buffer);

    String command = _buffer.substring(0, separatorIndex);

    // Serial.println("Command after:" + command);
    // Serial.print("Length:");
    // Serial.println(_buffer.length());

    long si = separatorIndex + _endMarker.length();
    if (si >= _buffer.length())
    {
        _buffer = "";
    }
    else
    {
        _buffer = _buffer.substring(si);
    }
    
    // Serial.println("Buffer after:" + _buffer);
    command.replace(_endLine, "");
    return command;
}

inline void Console::SetCommandEnding(String newEndMarker)
{
    _endMarker = newEndMarker;
}
