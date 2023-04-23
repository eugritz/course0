#pragma once

#include <SFML/Graphics.hpp>

#include <functional>

#include "linearray.h"

#define GRAPH_SCALE_START 10.f
#define GRAPH_SPIKE_DIFF 300.f
#define GRAPH_SCALE_MAX 20.f
#define GRAPH_SCALE_MIN 0.f
#define GRAPH_WIDTH 1.5f

struct Function {
    sf::Color color;
    std::function<float(float)> func;
};

class FuncGraph : public sf::Drawable {
    sf::Vector2f _absOrigin;
    sf::Vector2f _absCenter;
    sf::Vector2f _size;
    float _scale;

    sf::FloatRect _visibleArea;

    enum FuncDirection {
        CONTINUOUS = 0,
        DESCENDING,
        ASCENDING,
    };

    struct CachedFunction {
        Function func;
        LineArray lines;
    };

    std::vector<CachedFunction> _funcs;
    bool _needsRefresh;

public:
    FuncGraph();
    FuncGraph(const sf::Vector2u &size);

    void init();
    void create(const sf::Vector2u &size);

    void add(const Function &func);
    void update();

    void origin();
    void move(float dx, float dy);
    void scale(float delta);

    sf::Vector2f getOrigin() const;
    sf::Vector2f getCenter() const;

    sf::Vector2f absoluteCoords(float x, float y);
    sf::Vector2f absoluteCoords(const sf::Vector2f &relative);
    sf::Vector2f relativeCoords(float x, float y);
    sf::Vector2f relativeCoords(const sf::Vector2f &absolute);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void calculate(CachedFunction &cached);
};
