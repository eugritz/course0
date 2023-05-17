#pragma once

#include <SFML/Graphics.hpp>

#include "Scene.h"

class RacePlayerSelectScene : public Scene {
    bool _finishing;

public:
    RacePlayerSelectScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
};
