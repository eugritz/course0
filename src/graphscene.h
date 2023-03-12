#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "scene.h"

#define GRAPH_AXIS_WIDTH 2.f
#define GRAPH_AXIS_VALUES_INDENT 5.f
#define GRAPH_AXIS_VALUES_FONT_SIZE 10
#define GRAPH_LINE_WIDTH 3.f
#define GRAPH_SPIKE_DIFF 1000.f

class GraphScene : public Scene {
    sf::Vector2f _absOrigin;
    sf::Vector2f _absCenter;
    sf::Vector2f _size;
    float _scale;
    bool _smallGrid;
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
