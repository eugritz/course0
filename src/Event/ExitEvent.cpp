#include "ExitEvent.h"

#include "../Course0.h"

bool ExitEvent::run(Course0 *context) {
    context->exit();
    return true;
}
