#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "funcgraph.h"
#include "linearray.h"
#include "scene.h"

#define GRAPH_AXIS_ARROW_RADIUS 10.f
#define GRAPH_AXIS_LABEL_FONT_SIZE 14
#define GRAPH_AXIS_VALUES_INDENT 5.f
#define GRAPH_AXIS_VALUES_FONT_SIZE 10
#define GRAPH_AXIS_WIDTH 2.f
#define GRAPH_LABEL_THICKNESS 2.f
#define GRAPH_LINE_WIDTH 3.f

class GraphScene : public Scene {
    sf::Vector2u _size;
    sf::Vector2f _cursorPosition;
    bool _finishing;
    bool _grab;

    sf::Font _axisFont;

    enum FuncDirection {
        CONTINUOUS = 0,
        DESCENDING,
        ASCENDING,
    };

    FuncGraph _graph;
    LineArray _lines;
    bool _needsRefresh;

public:
    GraphScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void drawGrid();
    void drawAxes();
    void drawFunc();
    void drawAxesLabels();

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
    void onMouseMoved(const sf::Event::MouseMoveEvent &event);
    void onMouseButtonPressed(const sf::Event::MouseButtonEvent &event);
    void onMouseButtonReleased(const sf::Event::MouseButtonEvent &event);
    void onMouseWheelScrolled(const sf::Event::MouseWheelScrollEvent &event);
};
