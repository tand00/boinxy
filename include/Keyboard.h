#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Adafruit_MCP23X17.h>

#include <Button.h>

#define KEYBOARD_SIZE 14
#define FIRST_KEYBOARD_NOTE -1

class Keyboard {

    public:

        Keyboard();

        void setup();
        void update();

        ButtonState up() const;
        ButtonState down() const;

        ButtonState pianoKey(uint8_t i) const;
        ButtonState bottomKey(uint8_t i) const;
        ButtonState topKey(uint8_t i) const;

    private:

        Adafruit_MCP23X17 _mcp;

        Button _up;
        Button _down;

        Button _keys[KEYBOARD_SIZE];

};

#endif
