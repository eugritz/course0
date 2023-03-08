#pragma once

#include <SFML/Graphics.hpp>

#include "scene.h"

class MenuScene : public Scene {
    sf::RectangleShape _background;

public:
    MenuScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states) const;
    bool handleEvent(const sf::Event &event);
};
