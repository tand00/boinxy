#include <Instrument.h>

int Instrument::getSettingsCount() const
{
    return 0;
}

void Instrument::incrSetting(int i)
{
    this->configureSetting(i, this->getSettingValue(i) + 1);
}

void Instrument::decrSetting(int i)
{
    this->configureSetting(i, this->getSettingValue(i) - 1);
}

String Instrument::logSetting(int i)
{
    return String(getSettingName(i)) + " : " + getSettingValue(i);
}
