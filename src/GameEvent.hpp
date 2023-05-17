#pragma once

#include "RacePlayer.hpp"

class GameEvent {
public:
    struct RaceOpenEvent {
        PlayerType players[3]; // array size must equal to RACE_PLAYERS
        size_t selectedIndex;
    };

    enum EventType {
        IntroOpen,
        MenuOpen,
        SynthesizerOpen,
        RacePlayerSelectOpen,
        RaceOpen,
        AuthorOpen,
        Exit,
    } type;

    union {
        RaceOpenEvent raceOpen;
    };
};
