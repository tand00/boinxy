#include <JoyStick.h>

JoyStick::JoyStick(uint8_t pin_x, uint8_t pin_y) 
    : _x_pin(pin_x)
    , _y_pin(pin_y)
{ }

void JoyStick::setup()
{
    pinMode(_x_pin, INPUT);
    pinMode(_y_pin, INPUT);
}

ButtonState JoyStick::up() const
{
    return _up;
}

ButtonState JoyStick::down() const
{
    return _down;
}

ButtonState JoyStick::left() const
{
    return _left;
}

ButtonState JoyStick::right() const
{
    return _right;
}

void JoyStick::update()
{
    int xPosInt = analogRead(_x_pin) - 512;
    int yPosInt = analogRead(_y_pin) - 512;
    if(xPosInt < DOWN_THRESHOLD) {
        if(!pressed(_left)) _left = JustPressed;
        else _left = Pressed;
        if(pressed(_right)) _right = JustReleased;
        else _right = Released;
    } else if(xPosInt > UP_THRESHOLD) {
        if(pressed(_left)) _left = JustReleased;
        else _left = Released;
        if(!pressed(_right)) _right = JustPressed;
        else _right = Pressed;
    } else {
        if(pressed(_left)) _left = JustReleased;
        else _left = Released;
        if(pressed(_right)) _right = JustReleased;
        else _right = Released;
    }
    if(yPosInt < DOWN_THRESHOLD) {
        if(!pressed(_down)) _down = JustPressed;
        else _down = Pressed;
        if(pressed(_up)) _up = JustReleased;
        else _up = Released;
    } else if(yPosInt > UP_THRESHOLD) {
        if(pressed(_down)) _down = Released;
        else _down = Released;
        if(!pressed(_up)) _up = JustPressed;
        else _up = Pressed;
    } else {
        if(pressed(_down)) _down = Released;
        else _down = Released;
        if(pressed(_up)) _up = JustReleased;
        else _up = Released;
    }
    _x_pos = ((float) xPosInt) / 512.0;
    _y_pos = ((float) yPosInt) / 512.0;
}

float JoyStick::xPosition() const
{
    return _x_pos;
}

float JoyStick::yPosition() const
{
    return _y_pos;
}
