#include <Button.h>

#include <Arduino.h>

Button::Button(uint8_t pin) : _pin(pin) {
    
}

void Button::setup(bool pullup) {
    pinMode(_pin, pullup ? INPUT_PULLUP : INPUT);
}

ButtonState Button::state() const {
    return _state;
}

bool Button::pressed() const {
    return (_state == Pressed) || (_state == JustPressed);
}

ButtonState Button::update() {
    bool status = (digitalRead(_pin) == LOW);
    if(status) {
        if(!pressed()) _state = JustPressed;
        else _state = Pressed;
    } else {
        if(pressed()) _state = JustReleased;
        else _state = Released;
    }
    return _state;
}