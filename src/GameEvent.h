#pragma once

class Course0;

class GameEvent {
public:
    virtual bool run(Course0 *context) = 0;
};
