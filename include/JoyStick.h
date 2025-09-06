#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <Button.h>

#define DOWN_THRESHOLD (100)
#define UP_THRESHOLD (-100)

class JoyStick {

    public:

        JoyStick(uint8_t pin_x, uint8_t pin_y);

        void setup();

        ButtonState up() const;
        ButtonState down() const;
        ButtonState left() const;
        ButtonState right() const;

        void update();

        float xPosition() const;
        float yPosition() const;

    private:

        uint8_t _x_pin;
        uint8_t _y_pin;

        ButtonState _down = Released;
        ButtonState _up = Released;
        ButtonState _left = Released;
        ButtonState _right = Released;

        float _x_pos = 0.0;
        float _y_pos = 0.0;

};

#endif