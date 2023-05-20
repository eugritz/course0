#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.hpp"

class Timer : public sf::Drawable, public sf::Transformable {
    SharedResource<sf::Font> _font;
    sf::Text _text;

    sf::Time _duration, _fixedDuration;

public:
    Timer();
    Timer(const sf::Time &duration);
    void create(const sf::Time &duration);

    void update(const sf::Time &elapsed);

    bool isFinished() const;
    sf::Time getPassed() const;

    sf::Vector2f getSize() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
