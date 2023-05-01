#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>
#include <istream>

class Line : public sf::Shape {
    sf::Vector2f _start, _end;
    float _width;

public:
    Line(float width = 1.f);
    Line(const sf::Vector2f &start, const sf::Vector2f &end, float width = 1.f);

    void setPoints(const sf::Vector2f &start, const sf::Vector2f &end);
    sf::Vector2f getStart() const;
    sf::Vector2f getEnd() const;

    float getLength() const;
    sf::Vector2f getSize() const;

    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t index) const;

    sf::VertexArray toArray() const;

private:
    sf::Vector2f _rotate(float X, float Y, float rad) const;
};
