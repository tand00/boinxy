#include "Screen.h"

#include <BoinxState.h>

Screen::Screen()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{ }

void Screen::setup(BoinxState state)
{
    _cache_state = state;
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR)) {
        Serial.println("Unable to initialize display !");
        return;
    }
    display.clearDisplay();
    display.display();
    buildGenericScreen();
    display.display();
    Serial.println("Initialized Display !");
}

void Screen::update(BoinxState* state)
{
    if(_messageTimeout > MESSAGE_TIMEOUT) {
        _msg = "";
        _update = true;
    }
    if(state->has_changed(_cache_state)) {
        _update = true;
        _cache_state = *state;
    }
    if(_update) {
        display.clearDisplay();
        buildGenericScreen();
        display.display();
        _update = false;
    }
}

void Screen::buildGenericScreen()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(_cache_state.page()->name());
    if(_cache_state.alter) {
        display.setCursor(64, 0);
        display.print("ALT");
    }
    display.setCursor(0, 32);
    display.println(_msg);
}

void Screen::forceUpdate()
{
    _update = true;
}

void Screen::message(String msg)
{
    _msg = msg;
    _messageTimeout = 0;
    _update = true;
}
