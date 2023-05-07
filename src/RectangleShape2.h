#pragma once

#include <SFML/Graphics.hpp>

class RectangleShape2 : public sf::Shape {
    sf::Vector2f _size;
    std::size_t _iters;
    std::size_t _itersX;
    std::size_t _itersY;
    float _roundness;
    float _offset;
    float _step;

public:
    RectangleShape2();
    RectangleShape2(const sf::Vector2f &size, std::size_t iters = 1,
                    float roundness = 0.f);
    RectangleShape2(const sf::Vector2f &size, std::size_t iters = 1,
                    std::size_t itersX = 1, std::size_t itersY = 1,
                    float roundness = 0.f);

    const sf::Vector2f &getSize() const;
    void setSize(const sf::Vector2f &size);

    void setIterationCount(std::size_t iters);
    void setIterationCount(std::size_t iters, std::size_t itersX,
                           std::size_t itersY);
    void setRoundness(float roundness);

    std::size_t getPointCount() const;
    sf::Vector2f getPoint(std::size_t index) const;

    static sf::Vector2f bezier2(const sf::Vector2f &p0, const sf::Vector2f &p1,
                                const sf::Vector2f &p2, float t);

private:
    void init(const sf::Vector2f &size, std::size_t iters, float roundness);
    void calculateIters(std::size_t x, std::size_t y);
};
