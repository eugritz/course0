#include "Synthesizer.h"

#include <cmath>

Synthesizer::Synthesizer() {
    _stream = nullptr;
    _phase = 0;
}

Synthesizer::~Synthesizer() {
    stop();
    close();
}

int Synthesizer::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags) {
    float *out = (float *)outputBuffer;
    int i;

    double seconds_per_frame = 1.0 / (double)SAMPLE_RATE;

    for (i = 0; i < framesPerBuffer; i++) {
        double freq = _waveform->getFrequency();
        double sample = _waveform->getSample(_phase, (double)SAMPLE_RATE);
        *out++ = (float)sample;

        _phase += 1;
        while (_phase >= SAMPLE_RATE / freq)
            _phase -= SAMPLE_RATE / freq;
    }

    return paContinue;
}

void Synthesizer::setWaveform(std::shared_ptr<Waveform> waveform) {
    _waveform = waveform;
    _waveform->setStream(_stream);
}

bool Synthesizer::open(PaDeviceIndex deviceIndex) {
    PaStreamParameters outputParameters;
    outputParameters.device = deviceIndex;
    if (outputParameters.device == paNoDevice) {
        return false;
    }

    const PaDeviceInfo *info = Pa_GetDeviceInfo(deviceIndex);
    outputParameters.channelCount = 1;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = info->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    PaError err = Pa_OpenStream(
            &_stream,
            nullptr,
            &outputParameters,
            SAMPLE_RATE,
            paFramesPerBufferUnspecified,
            paClipOff,
            &Synthesizer::paCallback,
            this);
    if (err != paNoError) {
        return false;
    }

    return true;
}

bool Synthesizer::start() {
    if (_stream == nullptr)
        return false;
    PaError err = Pa_StartStream(_stream);
    return (err == paNoError);
}

bool Synthesizer::stop() {
    if (_stream == nullptr)
        return false;
    PaError err = Pa_StopStream(_stream);
    return (err == paNoError);
}

bool Synthesizer::close() {
    if (_stream == nullptr)
        return false;
    PaError err = Pa_CloseStream(_stream);
    _stream = nullptr;
    return (err == paNoError);
}


int Synthesizer::paCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData) {
    return ((Synthesizer *)userData)->paCallbackMethod(inputBuffer,
            outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}
