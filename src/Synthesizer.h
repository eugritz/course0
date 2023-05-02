#pragma once

#include <portaudio.h>

#include <atomic>
#include <cstdio>
#include <memory>

#include "Waveform.h"

#define SAMPLE_RATE 44100

class Synthesizer {
    PaStream *_stream;
    std::shared_ptr<Waveform> _waveform;
    int _phase;

public:
    Synthesizer();
    ~Synthesizer();

    bool open(PaDeviceIndex deviceIndex = Pa_GetDefaultOutputDevice());
    bool start();
    bool stop();
    bool close();

    void setWaveform(std::shared_ptr<Waveform> waveform);

private:
    int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags);

    static int paCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData);
};

class ScopedPaHandler {
    PaError _result;

public:
    ScopedPaHandler() {
#ifdef __linux__
        std::freopen("/dev/null", "w", stderr);
#endif
        _result = Pa_Initialize();
#ifdef __linux__
        std::freopen("/dev/tty", "w", stderr);
#endif
    }

    ~ScopedPaHandler() {
        if (_result == paNoError)
            Pa_Terminate();
    }

    PaError result() const {
        return _result;
    }
};
