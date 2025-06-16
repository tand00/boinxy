#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

enum ButtonState {
    JustReleased,
    Released,
    JustPressed,
    Pressed,
};

class Button {

    public:

        Button(uint8_t pin);

        void setup(bool pullup = true);
        ButtonState state() const;
        bool pressed() const;
        ButtonState update();

    private:

        uint8_t _pin;
        ButtonState _state = Released;
};

#endif