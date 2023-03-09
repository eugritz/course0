#pragma once

#include <SFML/Graphics.hpp>

#include "fragrect.hpp"
#include "scene.h"

#define MENU_COLOR_OFFSET_TIMEOUT 50

class MenuScene : public Scene {
    sf::RectangleShape _background;

    FragmentRectangleShape _r1, _r2, _r3, _r4;
    sf::Shader _borderShader;
    float _colorOffset;

public:
    MenuScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
