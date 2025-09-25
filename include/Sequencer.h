#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <Arduino.h>
#include <Event.h>

#define MAX_SEQUENCER_STEPS 256
#define MAX_EVENTS_PER_STEP 32

#define MAX_ACTIVE_EVENTS 128

#define DEFAULT_TEMPO 110
#define DEFAULT_TRACK_LEN 64
#define DEFAULT_STEP_PER_PULSE 4

enum SeqDirection {
    Paused = 0,
    Forward = 1,
    Backward = -1
};

class Sequencer {

    public:

        Sequencer();
    
        uint16_t getTempo() const;
        void setTempo(uint16_t tempo);
        void incrTempo();
        void decrTempo();

        int16_t getTrackLen() const;
        void setTrackLen(int16_t len);

        uint8_t getStepsPerPulse() const;
        void setStepsPerPulse(uint8_t spp);

        int16_t getCurrentStep() const;
        void setCurrentStep(int16_t step, bool reset_time = true);

        int16_t getCurrentPulse() const;

        int16_t getPreviousStep() const;
        
        void update();
        void reset();

        /// @brief Mark recording active, will start at next sequence
        void toggleRecord();
        void setRecord(const bool record);
        bool isRecording() const;
        void feed(Event& e);

        void playPause();
        bool isPaused() const;
        void pause();
        void backward();
        void forward();
        SeqDirection getDirection() const;

        unsigned long usStepLen() const;
        unsigned long usPulseLen() const;

        int16_t eventIndex(int16_t step, const Event& e) const;
        void addEvent(Event e);
        void addEvent(int16_t step, Event e);
        void removeEvent(int16_t step, const Event& e);
        void toggleEvent(int16_t step, Event e);
        void purgeInstrumentStep(int16_t step, int16_t instrument);
        void purgeInstrument(int16_t instrument);
        //uint8_t getEventsCount(int step) const;
        //uint8_t getEventsCount() const;
        Event* getEvents(int16_t step);
        Event* getEvents();
        Event* getPreviousEvents();

        Event* getActiveEvents();

        bool step_flag = false;
        bool sequence_flag = false;
        bool pulse_flag = false;

        bool auto_stop_record = true;

    private:

        int16_t findFreeEventIndex(int16_t step);

        bool updateActiveEvents(Event e);

        Event _active_events[MAX_ACTIVE_EVENTS];

        bool _recorded_events = false;

        uint16_t _tempo = DEFAULT_TEMPO;
        int16_t _track_len = DEFAULT_TRACK_LEN;
        int16_t _current_step = 0;
        elapsedMicros _elapsed = 0;
        int _date_backup = 0;

        uint8_t _steps_per_pulse = DEFAULT_STEP_PER_PULSE;

        bool _record = false;

        SeqDirection _direction = Forward;

        Event _events[MAX_SEQUENCER_STEPS][MAX_EVENTS_PER_STEP];
        //uint8_t _events_count[MAX_SEQUENCER_STEPS] = { 0 };
        
};

#endif
