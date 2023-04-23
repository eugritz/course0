#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <istream>

class Line : public sf::Shape {
    sf::Vector2f _start, _end;
    float _width;

public:
    Line(float width = 1.f) {
        _width = width;
        update();
    }

    Line(const sf::Vector2f &start, const sf::Vector2f &end,
            float width = 1.f) {
        setPoints(start, end);
    }

    void setPoints(const sf::Vector2f &start, const sf::Vector2f &end) {
        _start = start;
        _end = end;
        update();
    }

    sf::Vector2f getStart() const {
        return _start;
    }

    sf::Vector2f getEnd() const {
        return _end;
    }

    float getLength() const {
        float dx = _start.x - _end.x;
        float dy = _start.y - _end.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    sf::Vector2f getSize() const {
        return sf::Vector2f(getLength(), _width);
    }

    virtual std::size_t getPointCount() const {
        return 4;
    }

    virtual sf::Vector2f getPoint(std::size_t index) const {
        float rad = std::asin((_end.y - _start.y) / getLength());
        switch (index)
        {
            default:
            case 0: return _rotate(0, -_width, rad);
            case 1: return _rotate(getLength(), -_width, rad);
            case 2: return _rotate(getLength(), _width, rad);
            case 3: return _rotate(0, _width, rad);
        }
    }

    sf::VertexArray toArray() const {
        sf::VertexArray arr(sf::TriangleStrip, 4);
        arr[0] = getPoint(0);
        arr[1] = getPoint(3);
        arr[2] = getPoint(1);
        arr[3] = getPoint(2);

        arr[0].color = getFillColor();
        arr[1].color = getFillColor();
        arr[2].color = getFillColor();
        arr[3].color = getFillColor();
        return arr;
    }

private:
    sf::Vector2f _rotate(float X, float Y, float rad) const {
        float x = X * std::cos(rad) - Y * std::sin(rad);
        float y = X * std::sin(rad) + Y * std::cos(rad);
        return sf::Vector2f(_start.x + x, _start.y + y);
    }
};
