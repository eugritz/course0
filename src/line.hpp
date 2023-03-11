#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <istream>

class Line : public sf::Drawable, public sf::Transformable {
    sf::RectangleShape _rect;
    sf::Vector2f _start, _end;
    float _width;

public:
    Line(sf::Vector2f start, sf::Vector2f end, float width = 1.f) {
        _start = start;
        _end = end;
        _width = width;

        _rect.setSize(getSize());
        _rect.setOrigin(0, _width / 2.f);
        _rect.setPosition(_start);

        float rad = std::asin((_end.y - _start.y) / getLength());
        _rect.setRotation(rad / M_PI * 180.f);
    }

    void setFillColor(const sf::Color &color) {
        _rect.setFillColor(color);
    }
    
    void setOutlineColor(const sf::Color &color) {
        _rect.setOutlineColor(color);
    }

    void setOutlineThickness(float thickness) {
        _rect.setOutlineThickness(thickness);
    }

    float getLength() const {
        float dx = _start.x - _end.x;
        float dy = _start.y - _end.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(getLength(), _width);
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(_rect, states);
    }
};
