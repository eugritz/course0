#include "RaceOpenEvent.h"

#include "../Course0.h"
#include "../RaceScene.h"

RaceOpenEvent::RaceOpenEvent(PlayerOption options[3]) {
    const size_t playerCount = sizeof(_options) / sizeof(PlayerOption);
    for (size_t i = 0; i < playerCount; i++) {
        _options[i] = options[i];
    }
}

bool RaceOpenEvent::run(Course0 *context) {
    context->setScene(new RaceScene(&context->getWindow()));
    return true;
}
