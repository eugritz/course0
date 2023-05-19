#include "SynthesizerMenuOpenEvent.h"

#include "../Course0.h"
#include "../SynthesizerMenu.h"

bool SynthesizerMenuOpenEvent::run(Course0 *context) {
    context->setScene(new SynthesizerMenu(&context->getWindow()));
    return true;
}
