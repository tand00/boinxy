#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>

enum ButtonState {
    JustReleased,
    Released,
    JustPressed,
    Pressed,
};

class Button {

    public:

        Button(Adafruit_MCP23X17* mcp, uint8_t pin);

        void setup(bool pullup = true);
        ButtonState state() const;
        bool pressed() const;
        ButtonState update();

    private:

        uint8_t _pin;
        ButtonState _state = Released;
        Adafruit_MCP23X17* _mcp;
        
};

#endif