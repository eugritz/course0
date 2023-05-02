#pragma once

#include <portaudio.h>

class Waveform {
    PaStream *_stream;

public:
    virtual void start();
    virtual void stop();

    virtual double getSample(int phase, double sampleRate) const = 0;
    virtual double getFrequency() const = 0;

    virtual void setStream(PaStream *stream);

protected:
    bool _isStarted;
};
