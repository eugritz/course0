#include "AuthorMenuOpenEvent.h"

#include "../AuthorMenu.h"
#include "../Course0.h"

bool AuthorMenuOpenEvent::run(Course0 *context) {
    context->setScene(new AuthorMenu(&context->getWindow()));
    return true;
}
