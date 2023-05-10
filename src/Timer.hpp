#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "Resources.hpp"

class Timer : public sf::Drawable, public sf::Transformable {
    SharedResource<sf::Font> _font;
    sf::Text _text;

    sf::Time _duration, _fixedDuration;

public:
    Timer() { }
    Timer(const sf::Time &duration) {
        create(duration);
    }

    void create(const sf::Time &duration) {
        _font = GlobalResourceManager::ref<sf::Font>("TIMER_FONT");
        _duration = duration;
        _fixedDuration = duration;

        _text.setFont(**_font);
        _text.setString(std::to_string((int)std::ceil(_duration.asSeconds())));
        _text.setCharacterSize(128);

        _text.setFillColor(sf::Color::Red);
        _text.setOutlineThickness(5.f);
        _text.setOutlineColor(sf::Color::Black);
    }

    void update(const sf::Time &elapsed) {
        if (_duration.asSeconds() <= 0) {
            return;
        }

        _duration -= elapsed;
        _text.setString(std::to_string((int)std::ceil(_duration.asSeconds())));
    }

    bool isFinished() const {
        return _duration.asSeconds() <= 0;
    }

    sf::Time getPassed() const {
        return _fixedDuration - _duration;
    }

    sf::Vector2f getSize() const {
        return _text.getGlobalBounds().getSize();
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_text, states);
    }
};
