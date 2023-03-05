#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH 600
#define HEIGHT 500

#define FILL_TIMEOUT 100
#define FRAME_BLINK_TIMEOUT 500000

class Project0 {
    static Project0 *_instance;

    sf::RenderWindow _window;
    sf::Clock _clock;

public:
    static Project0 *getInstance();

    void start();
    void gameLoop();
};
