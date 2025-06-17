#ifndef BNX_AUDIO_H
#define BNX_AUDIO_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S2           micInput;         //xy=143,397
AudioEffectFreeverb      freeverb1;      //xy=159,57
AudioPlaySdWav           sdSamplePlayer1; //xy=233,163
AudioPlaySdWav           sdSamplePlayer3; //xy=234,300
AudioPlaySdWav           sdSamplePlayer2;     //xy=236,206
AudioPlaySdWav           sdSamplePlayer4; //xy=237,258
AudioMixer4              inputToMono;         //xy=333,435
AudioMixer4              SampleMixer1;         //xy=449,194
AudioMixer4              SampleMixer2; //xy=450,266
AudioPlayQueue           playingQueue;         //xy=450,348
AudioMixer4              SynthMixer;         //xy=455,78
AudioRecordQueue         recordQueue;         //xy=552,436
AudioMixer4              OutMixer;         //xy=738,240
AudioAmplifier           globalVolume;           //xy=945,240
AudioOutputI2S           i2sOutput;           //xy=1142,240
AudioConnection          patchCord1(micInput, 0, inputToMono, 0);
AudioConnection          patchCord2(micInput, 1, inputToMono, 1);
AudioConnection          patchCord3(sdSamplePlayer1, 0, SampleMixer1, 0);
AudioConnection          patchCord4(sdSamplePlayer1, 1, SampleMixer1, 1);
AudioConnection          patchCord5(sdSamplePlayer3, 0, SampleMixer2, 2);
AudioConnection          patchCord6(sdSamplePlayer3, 1, SampleMixer2, 3);
AudioConnection          patchCord7(sdSamplePlayer2, 0, SampleMixer1, 2);
AudioConnection          patchCord8(sdSamplePlayer2, 1, SampleMixer1, 3);
AudioConnection          patchCord9(sdSamplePlayer4, 0, SampleMixer2, 0);
AudioConnection          patchCord10(sdSamplePlayer4, 1, SampleMixer2, 1);
AudioConnection          patchCord11(inputToMono, recordQueue);
AudioConnection          patchCord12(SampleMixer1, 0, OutMixer, 1);
AudioConnection          patchCord13(SampleMixer2, 0, OutMixer, 2);
AudioConnection          patchCord14(playingQueue, 0, OutMixer, 3);
AudioConnection          patchCord15(SynthMixer, 0, OutMixer, 0);
AudioConnection          patchCord16(OutMixer, globalVolume);
AudioConnection          patchCord17(globalVolume, 0, i2sOutput, 0);
AudioConnection          patchCord18(globalVolume, 0, i2sOutput, 1);
// GUItool: end automatically generated code


#endif