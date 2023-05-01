#pragma once

#include <SFML/Graphics.hpp>

class Scene {
public:
    Scene(sf::RenderTarget *target) : _target(target) { }
    virtual ~Scene() = default;

    virtual void update(sf::Time elapsed) = 0;
    virtual void draw(sf::RenderStates states) = 0;
    virtual bool handleEvent(const sf::Event &event) = 0;

protected:
    sf::RenderTarget *_target;
};
