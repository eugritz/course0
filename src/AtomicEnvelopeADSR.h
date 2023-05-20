#pragma once

#include "Waveform.h"

#include <atomic>
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
    AtomicEnvelopeADSR(std::shared_ptr<Waveform> waveform);

    virtual double getSample(double sampleRate, PaTime time) override;

    virtual void start() override;
    virtual void stop() override;

    void setStream(PaStream *stream) override;

    virtual void setAttackDuration(double durationSeconds);
    virtual void setDecayDuration(double durationSeconds);
    virtual void setReleaseDuration(double durationSeconds);
    virtual void setAttackAmplitude(double amplitude);
    virtual void setSustainAmplitude(double amplitude);
};
