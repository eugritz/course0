#pragma once

#include "Waveform.h"

#include <atomic>
#include <iostream>
#include <memory>

class AtomicEnvelopeADSR : public Waveform {
    std::shared_ptr<Waveform> _waveform;
    std::atomic<PaTime> _startTime, _endTime;

    std::atomic<double> _attackDuration;
    std::atomic<double> _decayDuration;
    std::atomic<double> _releaseDuration;
    std::atomic<double> _attackAmplitude;
    std::atomic<double> _sustainAmplitude;

public:
    AtomicEnvelopeADSR(std::shared_ptr<Waveform> waveform) {
        _waveform = waveform;

        _attackDuration = 0.1;
        _decayDuration = 0.1;
        _releaseDuration = 0.1;
        _attackAmplitude = 1.0;
        _sustainAmplitude = 0.8;

        _startTime = 0.0;
        _endTime = 0.0;
    }

    virtual double getSample(double sampleRate, PaTime time) override {
        double amplitude = 0.0;
        PaTime lifeTime = time - _startTime;

        if (_isStarted) {
            if (lifeTime <= _attackDuration) {
                double attack = lifeTime / _attackDuration;
                amplitude = attack * _attackAmplitude;
            } else if (lifeTime - _attackDuration <= _decayDuration) {
                double decay = (lifeTime - _attackDuration) / _decayDuration;
                double step = _sustainAmplitude - _attackAmplitude;
                amplitude = _attackAmplitude + decay * step;
            } else {
                amplitude = _sustainAmplitude;
            }
        } else {
            double release = (time - _endTime) / _releaseDuration;
            amplitude = _sustainAmplitude - _sustainAmplitude * release;
        }

        if (amplitude <= 0.0001)
            return 0.0;
        return amplitude * _waveform->getSample(sampleRate, time);
    }

    virtual void start() override {
        if (_isStarted)
            return;
        Waveform::start();
        _waveform->start();
        _startTime = Pa_GetStreamTime(_stream);
    }

    virtual void stop() override {
        if (!_isStarted)
            return;
        Waveform::stop();
        _endTime = Pa_GetStreamTime(_stream);
    }

    void setStream(PaStream *stream) override {
        Waveform::setStream(stream);
        _waveform->setStream(stream);
    }

    virtual void setAttackDuration(double durationSeconds) {
        _attackDuration = durationSeconds;
    }

    virtual void setDecayDuration(double durationSeconds) {
        _decayDuration = durationSeconds;
    }

    virtual void setReleaseDuration(double durationSeconds) {
        _releaseDuration = durationSeconds;
    }

    virtual void setAttackAmplitude(double amplitude) {
        _attackAmplitude = amplitude;
    }

    virtual void setSustainAmplitude(double amplitude) {
        _sustainAmplitude = amplitude;
    }
};
