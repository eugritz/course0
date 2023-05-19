#pragma once

#include "../GameEvent.h"

class Course0;

class IntroOpenEvent : public GameEvent {
public:
    virtual bool run(Course0 *context);
};
