#include <SampleLibrary.h>

void SampleLibrary::setup()
{
    if(!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("Unable to initialize SD card !");
    }
    _root = SD.open(SAMPLES_PATH);
    _n_categories = countDirectory(_root);
    _category = _root.openNextFile();
    _category_index = 0;
    openCategory();
    Serial.println("Initialized samples library !");
    Serial.println(String(" - Found ") + _n_categories + " categories");
}

void SampleLibrary::reset()
{
    _sample.close();
    _category.close();
    _category = _root.openNextFile();
    _category_index = 0;
    openCategory();
}

void SampleLibrary::nextCategory()
{
    _sample.close();
    _category = _root.openNextFile();
    _category_index++;
    if(!_category) {
        _root.rewindDirectory();
        _category = _root.openNextFile();
        _category_index = 0;
    }
    openCategory();
}

void SampleLibrary::previousCategory()
{
    _sample.close();
    _category.close();
    uint16_t target = (_category_index == 0) ? (_n_categories - 1) : (_category_index - 1);
    _category = openFileN(_root, target);
    _category_index = target;
    openCategory();
}

uint16_t SampleLibrary::categoryIndex()
{
    return _category_index;
}

void SampleLibrary::nextSample()
{
    _sample = _category.openNextFile();
    _sample_index++;
    if(!_sample) {
        _category.rewindDirectory();
        _sample = _category.openNextFile();
        _sample_index = 0;
    }
}

void SampleLibrary::previousSample()
{
    _sample.close();
    uint16_t target = (_sample_index == 0) ? (_n_samples - 1) : (_sample_index - 1);
    _sample = openFileN(_category, target);
    _sample_index = target;
}

uint16_t SampleLibrary::sampleIndex()
{
    return _sample_index;
}

File *SampleLibrary::getCategory()
{
    return &_category;
}

File *SampleLibrary::getSample()
{
    return &_sample;
}

String SampleLibrary::getPath()
{
    return String(SAMPLES_PATH) + "/" + _category.name() + "/" + _sample.name();
}

uint16_t SampleLibrary::countDirectory(File &dir)
{
    uint16_t res = 0;
    File entry = dir.openNextFile();
    while(entry) {
        res++;
        entry = dir.openNextFile();
    }
    entry.close();
    dir.rewindDirectory();
    return res;
}

void SampleLibrary::openCategory()
{
    if(!_category.isDirectory()) {
        return;
    }
    _n_samples = countDirectory(_category);
    _sample = _category.openNextFile();
    _sample_index = 0;
}

File SampleLibrary::openFileN(File &dir, uint16_t n)
{
    dir.rewindDirectory();
    File entry;
    for(uint16_t i = 0 ; i < n ; i++) {
        entry = dir.openNextFile();
        if(!entry) {
            dir.rewindDirectory();
            entry = dir.openNextFile();
        }
    }
    return entry;
}
