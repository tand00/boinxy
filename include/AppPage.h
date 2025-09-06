#ifndef APP_PAGE_H
#define APP_PAGE_H

#include <Arduino.h>

class BoinxState;

class AppPage {
    
    public:
        
        virtual const char* name() const = 0;
        virtual void enter(BoinxState* state) {};
        virtual void update(BoinxState* state) = 0;
        virtual void leave(BoinxState* state) {};

};

#endif
