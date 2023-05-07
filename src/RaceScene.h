#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleShape2.h"
#include "Scene.h"

#define RACE_TRACK_SIZE_X 400.f
#define RACE_TRACK_SIZE_Y 200.f

class RaceScene : public Scene {
    sf::Vector2f _size;
    bool _finishing;
    RectangleShape2 _path;

public:
    RaceScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setup();

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
};