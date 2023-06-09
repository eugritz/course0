#pragma once

#include <SFML/Graphics.hpp>

#include <queue>
#include <memory>

#include "GameEvent.h"

#define WIDTH 600
#define HEIGHT 500

class Scene;

class Course0 {
    static Course0 *_instance;
    Scene *_scene;

    sf::RenderWindow _window;
    sf::Clock _clock;

    std::queue<std::shared_ptr<GameEvent>> _eventBus;

    Course0();
    Course0(const Course0 &);
    Course0 &operator=(Course0 &);

public:
    static Course0 *getInstance();

    void start();
    void gameLoop();
    void exit();

    sf::RenderWindow &getWindow();

    void setScene(Scene *scene);
    void postEvent(std::shared_ptr<GameEvent> event);
};
