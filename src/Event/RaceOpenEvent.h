#pragma once

#include "../GameEvent.h"
#include "../RacePlayer.hpp"

class Course0;

class RaceOpenEvent : public GameEvent {
    PlayerOption _options[3];

public:
    RaceOpenEvent(PlayerOption options[3]);

    virtual bool run(Course0 *context);
};
