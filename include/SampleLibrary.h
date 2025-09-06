#ifndef SAMPLE_LIBRARY_H
#define SAMPLE_LIBRARY_H

#include <Arduino.h>
#include <SD.h>

#define SAMPLES_PATH "/samples"

class SampleLibrary {

    public:

        void setup();

        void reset();

        void nextCategory();
        void previousCategory();
        uint16_t categoryIndex();

        void nextSample();
        void previousSample();
        uint16_t sampleIndex();

        File* getCategory();
        File* getSample();

        String getPath();

    private:

        uint16_t countDirectory(File& dir);
        void openCategory();
        File openFileN(File& dir, uint16_t n);

        File _root;
        File _category;
        File _sample;
        uint16_t _category_index = 0;
        uint16_t _sample_index = 0;
        uint16_t _n_categories;
        uint16_t _n_samples;

};

#endif