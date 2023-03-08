#pragma once

#include <SFML/Graphics.hpp>

class Scene  {
public:
    virtual ~Scene() = default;
    virtual void update(sf::Time elapsed) = 0;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual bool handleEvent(const sf::Event &event) = 0;
};
