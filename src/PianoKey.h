#pragma once

#include <SFML/Graphics.hpp>

class PianoKey : public sf::Drawable, public sf::Transformable {
public:
    virtual void setKeyPressed(bool isPressed) {
        _isPressed = isPressed;
    }

    virtual sf::Vector2f getSize() const = 0;

protected:
    bool _isPressed;
};
