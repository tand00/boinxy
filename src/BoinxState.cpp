#include <BoinxState.h>

void BoinxState::execute(Event e) const 
{
    instruments[e.instrument]->onEvent(e);
}