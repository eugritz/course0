#include "Synthesizer.h"

#include <cmath>

Synthesizer::Synthesizer() {
    _stream = nullptr;
    _phase = 0;
    _pitch = 0.0;
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
        double pitch = _pitch;
        double radians = pitch * 2.0 * M_PI;
        float sample = (float)std::sin(
                (double)_phase * seconds_per_frame * radians
                );

        if (pitch == 0.0)
            *out++ = 0.f;
        else if (sample > 0.f)
            *out++ = 0.1f;
        else
            *out++ = -0.1f;

        _phase += 1;
        if (_phase >= TABLE_SIZE) _phase -= TABLE_SIZE;
    }

    return paContinue;
}

void Synthesizer::setSemitone(int nth) {
    if (nth == 0) {
        _pitch = 0.0;
        return;
    }

    double octaveBaseFrequency = 110.0;
    double octaveMultiplier = std::pow(2.0, 1.0 / 12.0);
    _pitch = octaveBaseFrequency * pow(octaveMultiplier, nth - 1);
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
