#ifndef APP_PAGE_H
#define APP_PAGE_H

#include <Arduino.h>
#include "BoinxState.h"

class AppPage {
    
    public:

        AppPage(BoinxState* state)
            : _state(state) {}
        
        virtual void enter() {};
        virtual void update() = 0;
        virtual void leave() {};

    private:

        BoinxState* _state = nullptr;

};

#endif
