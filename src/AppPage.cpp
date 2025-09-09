#include <AppPage.h>

void AppPage::checkDisplayUpdate(BoinxState *state)
{
    if(_updateDisplay) {
        this->display(state);
        _updateDisplay = false;
    }
}

void AppPage::markForUpdate()
{
    _updateDisplay = true;
}
