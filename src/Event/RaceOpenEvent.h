#pragma once

#include "../GameEvent.h"
#include "../RacePlayer.h"

class Course0;

class RaceOpenEvent : public GameEvent {
    PlayerOption _options[3];
    size_t _selected;

public:
    RaceOpenEvent(PlayerOption options[3], size_t selected);

    virtual bool run(Course0 *context);
};
