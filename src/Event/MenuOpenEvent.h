#pragma once

#include "../GameEvent.h"

class Course0;

class MenuOpenEvent : public GameEvent {
public:
    virtual bool run(Course0 *context);
};
