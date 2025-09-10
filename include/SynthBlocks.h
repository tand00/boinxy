#ifndef SYNTH_BLOCKS_H
#define SYNTH_BLOCKS_H

#include <Arduino.h>
#include <Audio.h>

struct QuadWaveUnion {
    AudioSynthWaveform waves[4];
    AudioMixer4 out;
    AudioConnection con[4];
    
    QuadWaveUnion() { 
        for(int i = 0 ; i < 4 ; i++) {
            con[i].connect(waves[i], 0, out, i);
        }
        waves[0].begin(1.0, 440.0, WAVEFORM_SAWTOOTH);
        waves[1].begin(1.0, 440.0, WAVEFORM_SINE);
        waves[2].begin(1.0, 440.0, WAVEFORM_TRIANGLE);
        waves[3].begin(1.0, 440.0, WAVEFORM_SQUARE);
    }

    void begin(short type1, short type2, short type3, short type4) {
        waves[0].begin(type1);
        waves[1].begin(type1);
        waves[2].begin(type1);
        waves[3].begin(type1);
    }

    void freq(float f) {
        for(int i = 0 ; i < 4 ; i++) {
            waves[i].frequency(f);
        }
    }
};

#endif