#pragma once

#include <SFML/Graphics.hpp>

#include <queue>

#define WIDTH 600
#define HEIGHT 500

class Scene;

enum GameEvent {
    INTRO_OPEN,
    MENU_OPEN,
    SYNTHESIZER_OPEN,
    AUTHOR_OPEN,
    EXIT,
};

class Course0 {
    static Course0 *_instance;
    Scene *_scene;

    sf::RenderWindow _window;
    sf::Clock _clock;

    std::queue<GameEvent> _eventBus;

public:
    static Course0 *getInstance();

    void start();
    void gameLoop();
    void handleGameEvent(GameEvent event);

    void postEvent(GameEvent event);
};
