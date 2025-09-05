#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <BoinxState.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDR 0x3C

#define MESSAGE_TIMEOUT 2000

class Screen {

    public:

        Screen();

        void setup();
        void update(BoinxState* state);

        void buildGenericScreen();

        void forceUpdate();

        void message(String msg);

        Adafruit_SSD1306 display;

    private:

        elapsedMillis _messageTimeout;
        String _msg;
        bool _update = false;

        BoinxState cache_state;

};

#endif