#include <Screen.h>

#include <BoinxState.h>
#include <AppPage.h>

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
    if(_messageTimeout > MESSAGE_TIMEOUT && _msg.length() > 0) {
        _msg = "";
        _update = true;
    }
    if(state->has_changed(_cache_state)) {
        _update = true;
        _cache_state = *state;
    }
    if(state->sequencer->pulse_flag) {
        _pulse = 1 + (state->sequencer->getCurrentPulse() % 4);
        _update = true;
    }
    if(state->sequencer->isRecording() != _recording) {
        _recording = state->sequencer->isRecording();
        _update = true;
    }
    _update |= state->page()->needsScreenUpdate();
    if(_update) {
        display.clearDisplay();
        state->page()->display(state);
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
        display.print("FN");
    }
    display.setCursor(120, 0);
    display.print(String("") + _pulse);
    if(_recording) {
        display.setCursor(110, 0);
        display.print("o");
    }
    display.drawLine(0, 10, 128, 10, WHITE);
    display.setCursor(0,16);
    display.print(_page_msg);
    if(_msg.length() > 0) {
        display.fillRoundRect(0, 16, 128, 32, 10, BLACK);
        display.drawRoundRect(0, 16, 128, 32, 10, WHITE);
        int16_t x,y;
        uint16_t w,h;
        display.getTextBounds(_msg, 0, 24, &x, &y, &w, &h);
        if(w > 128) {
            x = 0;
        } else {
            x = 64 - w / 2;
        }
        if(h > 32) {
            y = 0;
        } else {
            y = 32 - h / 2;
        }
        display.setCursor(x,y);
        display.println(_msg);
    }
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

void Screen::pageMessage(String msg)
{
    _page_msg = msg;
    _update = true;
}

void Screen::clearPageMessage()
{
    pageMessage(String());
}
