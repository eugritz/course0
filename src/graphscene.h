#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "scene.h"

#define GRAPH_AXIS_WIDTH 2.f
#define GRAPH_AXIS_VALUES_INDENT 5.f
#define GRAPH_AXIS_VALUES_FONT_SIZE 12
#define GRAPH_LINE_WIDTH 3.f

// №16, a=2, b=4, n=12,
// F1(x) = powf(2.f, x)*log10f(x) - powf(3.f, x)*log10f(x)
// F2(x) = 1.f/tanf(x)

class GraphScene : public Scene {
    sf::Vector2f _absOrigin;
    sf::Vector2f _absCenter;
    sf::Vector2f _size;
    float _scale;
    bool _finishing;

    sf::Font _axisFont;

    enum FuncDirection {
        CONTINUOUS = 0,
        DESCENDING,
        ASCENDING,
    };

public:
    GraphScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void drawGrid();
    void drawAxes();
    void drawAxesLabels();
    void drawFunc(const sf::Color &color, std::function<float(float)> func);

    sf::Vector2f absoluteCoords(float x, float y);
    sf::Vector2f absoluteCoords(const sf::Vector2f &relative);
};
