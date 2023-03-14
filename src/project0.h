#pragma once

#include <SFML/Graphics.hpp>

#include <queue>

#define WIDTH 600
#define HEIGHT 500

class Scene;

enum GameEvent {
    INTRO_OPEN,
    MENU_OPEN,
    GRAPHS_OPEN,
    TABLE_OPEN,
    SOLUTION_OPEN,
    INTEGRAL_OPEN,
    AUTHOR_OPEN,
};

class Project0 {
    static Project0 *_instance;
    Scene *_scene;

    sf::RenderWindow _window;
    sf::Clock _clock;

    std::queue<GameEvent> _eventBus;

public:
    static Project0 *getInstance();

    void start();
    void gameLoop();
    void handleGameEvent(GameEvent event);

    void postEvent(GameEvent event);
};
