#ifndef BNX_AUDIO_H
#define BNX_AUDIO_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=94,205
AudioEffectEnvelope      envelope1;      //xy=272,205
AudioInputI2S2           i2s2_1;         //xy=461,329
AudioSynthSimpleDrum     drum1;          //xy=463,377
AudioPlaySdWav           playSdWav1;     //xy=470,275
AudioEffectFreeverb      freeverb1;      //xy=472,203
AudioMixer4              mixer1;         //xy=686,275
AudioOutputI2S           i2s2;           //xy=884,290
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, freeverb1);
AudioConnection          patchCord3(i2s2_1, 0, mixer1, 2);
AudioConnection          patchCord4(drum1, 0, mixer1, 3);
AudioConnection          patchCord5(playSdWav1, 0, mixer1, 1);
AudioConnection          patchCord6(freeverb1, 0, mixer1, 0);
AudioConnection          patchCord7(mixer1, 0, i2s2, 0);
// GUItool: end automatically generated code

#endif