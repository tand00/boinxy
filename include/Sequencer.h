#ifndef SEQUENCER_H
#define SEQUENCER_H

#define MAX_SEQUENCER_STEPS 64

#include <Arduino.h>

enum SeqDirection {
    Paused = 0,
    Forward = 1,
    Backward = -1
};

class Sequencer {

    public:
    
        unsigned int getTempo() const;
        void setTempo(unsigned int tempo);
        void incrTempo();
        void decrTempo();

        unsigned int getTrackLen() const;
        void setTrackLen(unsigned int len);

        unsigned int getCurrentStep() const;
        void setCurrentStep(unsigned int step);
        
        void update();
        void reset();
        void triggerStep();

        void pause();
        void backward();
        void forward();
        SeqDirection getDirection() const;

        int usStepLen();

        bool step_flag = false;

    private:

        unsigned int _tempo = 80;
        unsigned int _track_len = 16;
        unsigned int _current_step = 0;
        elapsedMicros _elapsed = 0;
        int _date_backup = 0;

        SeqDirection _direction = Forward;
        
};

#endif
