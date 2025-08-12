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
AudioMixer4              inputToMono;         //xy=333,435
AudioPlayQueue           playingQueue;         //xy=450,348
AudioMixer4              synthMixer;         //xy=455,78
AudioRecordQueue         recordQueue;         //xy=552,436
AudioMixer4              outMixer;         //xy=738,240
AudioAmplifier           globalVolume;           //xy=945,240
AudioOutputI2S           i2sOutput;           //xy=1142,240
AudioConnection          patchCord1(micInput, 0, inputToMono, 0);
AudioConnection          patchCord2(micInput, 1, inputToMono, 1);
AudioConnection          patchCord11(inputToMono, recordQueue);
AudioConnection          patchCord14(playingQueue, 0, outMixer, 3);
AudioConnection          patchCord15(synthMixer, 0, outMixer, 0);
AudioConnection          patchCord16(outMixer, globalVolume);
AudioConnection          patchCord17(globalVolume, 0, i2sOutput, 0);
AudioConnection          patchCord18(globalVolume, 0, i2sOutput, 1);
// GUItool: end automatically generated code


#endif