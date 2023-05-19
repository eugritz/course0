#include "RacePlayerSelectionOpenEvent.h"

#include "../Course0.h"
#include "../RacePlayerSelectionScene.h"

bool RacePlayerSelectionOpenEvent::run(Course0 *context) {
    context->setScene(new RacePlayerSelectionScene(&context->getWindow()));
    return true;
}
