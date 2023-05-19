#include "IntroOpenEvent.h"

#include "../Course0.h"
#include "../IntroScene.h"

bool IntroOpenEvent::run(Course0 *context) {
    context->setScene(new IntroScene(&context->getWindow()));
    return true;
}
