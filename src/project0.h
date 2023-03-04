#pragma once

#include <SFML/Graphics.hpp>

#define SCALE 0.005

class Project0 {
    static Project0 *_instance;

    sf::RenderWindow _window;
    sf::Clock _clock;

public:
    static Project0 *getInstance();

    void start();
    void gameLoop();
};
