#include <LivePage.h>

const char *LivePage::name() const
{
    return "Live";
}

void LivePage::update(BoinxState* state)
{
    
}

void LivePage::toggleRecord() 
{
    _record = !_record;
}