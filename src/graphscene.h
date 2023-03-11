#pragma once

#include <SFML/Graphics.hpp>

#include "scene.h"

// №16, a=2, b=4, n=12,
// F1(x) = powf(2.f, x)*log10f(x) - powf(3.f, x)*log10f(x)
// F2(x) = 1.f/tanf(x)

class GraphScene : public Scene {
    bool _finishing;

public:
    GraphScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);
};
