#include <Keyboard.h>

#define BUTTON_UP 0
#define BUTTON_DOWN 1

PROGMEM const uint8_t PINS[KEYBOARD_SIZE] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15 };
PROGMEM const uint8_t BOTTOM_KEYS[9] = {0, 1, 3, 5, 6, 8, 10, 12, 13};
PROGMEM const uint8_t TOP_KEYS[5] = {2, 4, 7, 9, 11};

Keyboard::Keyboard() 
    : _up(&_mcp, BUTTON_UP)
    , _down(&_mcp, BUTTON_DOWN)
    , _keys{
        Button(&_mcp, PINS[0]), Button(&_mcp, PINS[1]),
        Button(&_mcp, PINS[2]), Button(&_mcp, PINS[3]),
        Button(&_mcp, PINS[4]), Button(&_mcp, PINS[5]),
        Button(&_mcp, PINS[6]), Button(&_mcp, PINS[7]),
        Button(&_mcp, PINS[8]), Button(&_mcp, PINS[9]),
        Button(&_mcp, PINS[10]), Button(&_mcp, PINS[11]),
        Button(&_mcp, PINS[12]), Button(&_mcp, PINS[13]),
    }
{ }

void Keyboard::setup() 
{
    if(!_mcp.begin_I2C(MCP23XXX_ADDR)) {
        Serial.println("Unable to initialize MCP !");
    }
    _up.setup();
    _down.setup();
    for(int i = 0 ; i < 14 ; i++) {
        _keys[i].setup();
    }
    Serial.println("Initialized MCP !");
}

void Keyboard::update() 
{
    _up.update();
    _down.update();
    for(int i = 0 ; i < 14 ; i++) {
        _keys[i].update();
    }
}

ButtonState Keyboard::up() const
{
    return _up.state();
}

ButtonState Keyboard::down() const
{
    return _down.state();
}

ButtonState Keyboard::pianoKey(uint8_t i) const
{
    return _keys[i % KEYBOARD_SIZE].state();
}

ButtonState Keyboard::bottomKey(uint8_t i) const
{
    return _keys[BOTTOM_KEYS[i % 9]].state();
}

ButtonState Keyboard::topKey(uint8_t i) const
{
    return _keys[TOP_KEYS[i % 5]].state();
}
