#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <Event.h>
#include <Audio.h>

class Instrument {

    public:

        virtual void onEvent(Event) = 0;
        virtual const char* getName() const = 0;
        virtual const String getActionName(int16_t i) const = 0;

        virtual uint8_t getSettingsCount() const;
        virtual const char* getSettingName(uint8_t i) const { return "unknown"; }
        virtual void configureSetting(uint8_t setting, int value) {}
        virtual int getSettingValue(uint8_t i) const { return 0; }

        virtual void analogInputX(float value) {}
        virtual void analogInputY(float value) {}

        void incrSetting(uint8_t i);
        void decrSetting(uint8_t i);

        virtual String logSetting(uint8_t i);

        virtual void update() {}

        virtual AudioStream& getOutput() = 0;

};

#endif
