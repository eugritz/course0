#pragma once

#include <portaudio.h>

class Waveform {
public:
    virtual void start();
    virtual void stop();

    virtual double getSample(double sampleRate, PaTime time, int phase) const = 0;
    virtual double getFrequency() const = 0;

    virtual void setStream(PaStream *stream);

protected:
    PaStream *_stream;
    bool _isStarted;
};
