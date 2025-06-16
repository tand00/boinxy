#ifndef APP_PAGE_H
#define APP_PAGE_H

#include <Arduino.h>
#include "BoinxState.h"

class AppPage {
    public:
        AppPage(GlobalSettings* settings)
            : _settings(settings) {}
        
        virtual void enter() {};
        virtual void update() = 0;
        virtual void leave() {};
    private:
        GlobalSettings* _settings = nullptr;
};

#endif
