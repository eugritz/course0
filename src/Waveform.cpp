#include "Waveform.h"

void Waveform::start() {
    _isStarted = true;
}

void Waveform::stop() {
    _isStarted = false;
}

void Waveform::setStream(PaStream *stream) {
    _stream = stream;
    _isStarted = false;
}
