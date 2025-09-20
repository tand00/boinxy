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

class BoinxState;

class Screen {

    public:

        Screen();

        void setup(BoinxState state);
        void update(BoinxState* state);

        void buildGenericScreen();

        void forceUpdate();

        void message(String msg);
        void pageMessage(String msg);
        void clearPageMessage();

        Adafruit_SSD1306 display;

    private:

        elapsedMillis _messageTimeout;
        int _pulse = 1;
        bool _recording = false;
        String _msg;
        String _page_msg;
        bool _update = false;

        BoinxState _cache_state;

};

#endif