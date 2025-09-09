#ifndef SOLFAGUS_H
#define SOLFAGUS_H

#include <Arduino.h>

const int8_t NOTE_C = 0;
const int8_t NOTE_Cs = 1;
const int8_t NOTE_Db = 1;
const int8_t NOTE_D = 2;
const int8_t NOTE_Ds = 3;
const int8_t NOTE_Eb = 3;
const int8_t NOTE_E = 4;
const int8_t NOTE_F = 5;
const int8_t NOTE_Fs = 6;
const int8_t NOTE_Gb = 6;
const int8_t NOTE_G = 7;
const int8_t NOTE_Gs = 8;
const int8_t NOTE_Ab = 8;
const int8_t NOTE_A = 9;
const int8_t NOTE_As = 10;
const int8_t NOTE_Bb = 10;
const int8_t NOTE_B = 11;

enum KeyType {
    Chromatic,
    Major,
    Minor,
    PentatonicMajor,
    PentatonicMinor,
    Blues
};

struct Key {
    int8_t tonic;
    KeyType type;

    public:
        
        Key basic() const;
        String toString() const;
};

class Solfagus {

    public:

        void setKey(const Key key);
        Key getKey() const;

        void setKeyTonic(const int8_t tonic);
        void setKeyType(const KeyType type);

        static int8_t noteAtIndex(const Key& scale, const int8_t index);
        /// Note at given degree in the current key
        int8_t noteAt(const int8_t index) const;
    
        int8_t chordNote(const int8_t root_index, const int8_t index) const;
        void chordAt(const int8_t root_index, int8_t notes[], uint8_t n = 4) const;
        void chord(int8_t notes[], uint8_t n = 4) const;

        void majorChord(int8_t notes[], uint8_t n = 4) const;
        void minorChord(int8_t notes[], uint8_t n = 4) const;
        void dimChord(int8_t notes[], uint8_t n = 4) const;
        void dom7Chord(int8_t notes[], uint8_t n = 4) const;

        static double noteFrequency(int8_t note);
        static String noteName(int8_t note);

    private:

        Key _key = { 0, Major };

};

#endif