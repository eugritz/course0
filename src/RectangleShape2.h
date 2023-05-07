#pragma once

#include <SFML/Graphics.hpp>

class RectangleShape2 : public sf::Shape {
    sf::Vector2f _size;
    std::size_t _iters;
    float _rounding;
    float _offset;
    float _step;

public:
    RectangleShape2();
    RectangleShape2(sf::Vector2f size, std::size_t iters = 1, float rounding = 0.f);

    const sf::Vector2f &getSize() const;
    void setSize(const sf::Vector2f &size);

    void setIterationCount(std::size_t iters);
    void setRounding(float rounding);

    std::size_t getPointCount() const;
    sf::Vector2f getPoint(std::size_t index) const;
};
