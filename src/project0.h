#pragma once

#include <SFML/Graphics.hpp>

#define WIDTH 600
#define HEIGHT 500

class Scene;

class Project0 {
    static Project0 *_instance;
    Scene *_scene;

    sf::RenderWindow _window;
    sf::Clock _clock;

public:
    static Project0 *getInstance();

    void start();
    void gameLoop();
};
