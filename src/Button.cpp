#include <Button.h>

#include <Arduino.h>

Button::Button(Adafruit_MCP23X17* mcp, uint8_t pin) 
    : _pin(pin)
    , _mcp(mcp)
{ }

void Button::setup(bool pullup) 
{
    _mcp->pinMode(_pin, pullup ? INPUT_PULLUP : INPUT);
}

ButtonState Button::state() const 
{
    return _state;
}

bool Button::pressed() const 
{
    return (_state == Pressed) || (_state == JustPressed);
}

ButtonState Button::update() 
{
    bool status = (_mcp->digitalRead(_pin) == LOW);
    if(status) {
        if(!pressed()) _state = JustPressed;
        else _state = Pressed;
    } else {
        if(pressed()) _state = JustReleased;
        else _state = Released;
    }
    return _state;
}