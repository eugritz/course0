#pragma once

#include <SFML/Graphics.hpp>

class RectangleShape2 : public sf::Shape {
    sf::Vector2f _size;
    std::size_t _iters;
    std::size_t _itersX;
    std::size_t _itersY;
    bool _fractured;
    float _roundness;
    float _length;
    float _offset;
    float _step;

public:
    RectangleShape2();
    RectangleShape2(const sf::Vector2f &size, std::size_t iters = 1,
                    float roundness = 0.f, bool fractured = false);

    const sf::Vector2f &getSize() const;
    void setSize(const sf::Vector2f &size);

    std::size_t getIterationCount() const;
    void setIterationCount(std::size_t iters, bool fractured = false);
    void setRoundness(float roundness);

    std::size_t getPointCount() const;
    sf::Vector2f getPoint(std::size_t index) const;

    float getCurveLength() const;

    static sf::Vector2f bezier2(const sf::Vector2f &p0, const sf::Vector2f &p1,
                                const sf::Vector2f &p2, float t);
    static float bezier2Length(std::size_t iters, const sf::Vector2f &p0,
                               const sf::Vector2f &p1,
                               const sf::Vector2f &p2);

private:
    void init(const sf::Vector2f &size, std::size_t iters, float roundness,
              bool fractured);
    void calculateIters();
};
