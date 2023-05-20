#include "RaceOpenEvent.h"

#include "../Course0.h"
#include "../RaceScene.h"

RaceOpenEvent::RaceOpenEvent(PlayerOption options[3], size_t selected) {
    const size_t playerCount = sizeof(_options) / sizeof(PlayerOption);
    for (size_t i = 0; i < playerCount; i++) {
        _options[i] = options[i];
    }
    _selected = selected;
}

bool RaceOpenEvent::run(Course0 *context) {
    context->setScene(new RaceScene(&context->getWindow(), _options, _selected));
    return true;
}
