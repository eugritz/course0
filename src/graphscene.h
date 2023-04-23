#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "scene.h"

#define GRAPH_AXIS_ARROW_RADIUS 10.f
#define GRAPH_AXIS_LABEL_FONT_SIZE 14
#define GRAPH_AXIS_VALUES_INDENT 5.f
#define GRAPH_AXIS_VALUES_FONT_SIZE 10
#define GRAPH_AXIS_WIDTH 2.f
#define GRAPH_LABEL_THICKNESS 2.f
#define GRAPH_LINE_WIDTH 3.f
#define GRAPH_SCALE_START 10.f
#define GRAPH_SCALE_MAX 20.f
#define GRAPH_SCALE_MIN 0.f
#define GRAPH_SPIKE_DIFF 300.f
#define GRAPH_WIDTH 1.5f

class GraphScene : public Scene {
    sf::Vector2f _absOrigin;
    sf::Vector2f _absCenter;
    sf::Vector2f _size;
    float _scale;

    sf::Vector2f _cursorPosition;
    bool _finishing;
    bool _grab;

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

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
    void onMouseMoved(const sf::Event::MouseMoveEvent &event);
    void onMouseButtonPressed(const sf::Event::MouseButtonEvent &event);
    void onMouseButtonReleased(const sf::Event::MouseButtonEvent &event);
    void onMouseWheelScrolled(const sf::Event::MouseWheelScrollEvent &event);

    void scale(float delta);

    sf::Vector2f absoluteCoords(float x, float y);
    sf::Vector2f absoluteCoords(const sf::Vector2f &relative);
    sf::Vector2f relativeCoords(float x, float y);
    sf::Vector2f relativeCoords(const sf::Vector2f &absolute);
};
