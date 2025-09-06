#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <Button.h>
#include <Bounce.h>

#define DOWN_THRESHOLD (-300)
#define UP_THRESHOLD (300)

class JoyStick {

    public:

        JoyStick(uint8_t pin_x, uint8_t pin_y, uint8_t pin_btn);

        void setup();

        ButtonState up() const;
        ButtonState down() const;
        ButtonState left() const;
        ButtonState right() const;

        void update();

        float xPosition() const;
        float yPosition() const;

        Bounce button;

    private:

        uint8_t _x_pin;
        uint8_t _y_pin;
        uint8_t _btn_pin;

        ButtonState _down = Released;
        ButtonState _up = Released;
        ButtonState _left = Released;
        ButtonState _right = Released;

        float _x_pos = 0.0;
        float _y_pos = 0.0;

};

#endif