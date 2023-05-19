#include "MenuOpenEvent.h"

#include "../MainMenu.h"
#include "../Course0.h"

bool MenuOpenEvent::run(Course0 *context) {
    context->setScene(new MainMenu(&context->getWindow()));
    return true;
}
