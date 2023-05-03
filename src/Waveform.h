#pragma once

#include <portaudio.h>

class Waveform {
public:
    virtual void start();
    virtual bool isStarted();
    virtual void stop();

    virtual double getSample(double sampleRate, PaTime time) = 0;
    virtual void setStream(PaStream *stream);

protected:
    PaStream *_stream;
    bool _isStarted;
};
