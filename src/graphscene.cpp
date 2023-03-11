#include "graphscene.h"

#include <cmath>
#include <iostream>

#include "line.hpp"
#include "project0.h"

const sf::Color first = sf::Color(180, 20, 20);
const sf::Color second = sf::Color(40, 40, 160);

GraphScene::GraphScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2u size = target->getSize();
    _size.x = size.x;
    _size.y = size.y;
    _absCenter.x = size.x / 2.f;
    _absCenter.y = size.y / 2.f;
    _absOrigin = _absCenter;
    _finishing = false;

    if (!_axisFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
    }

    _scale = 10.f;
}

void GraphScene::update(sf::Time elapsed) { }

void GraphScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color::White);
    drawGrid();
    drawAxes();

    drawFunc(first, [](float x) {
        return 1.f / std::tan(x);
    });

    drawFunc(second, [](float x) {
        return std::pow(2.f, x)*std::log10(x) - std::pow(3.f, x)*std::log10(x);
    });

    drawAxesLabels();
}

void GraphScene::drawGrid() {
    const float labelIndent = GRAPH_AXIS_VALUES_INDENT;
    const float step = _scale / 10.f;
    const sf::Color verticalColor = sf::Color(0, 0, 0, 30);
    const sf::Color horizontalColor = sf::Color(0, 0, 0, 40);
    const sf::Color bigShadow = sf::Color(0, 0, 0, 5);

    for (float x = -_scale + step; x < _scale; x += step) {
        sf::Vector2f posX = absoluteCoords(x, 0),
            posY = absoluteCoords(0, x);

        std::string label = std::to_string(x);
        while (label.back() == '0')
            label.pop_back();
        while (label.back() == '.')
            label.pop_back();

        sf::Text axisXLabel(label, _axisFont, GRAPH_AXIS_VALUES_FONT_SIZE);
        axisXLabel.setOutlineThickness(2.f);
        axisXLabel.setOutlineColor(sf::Color::White);
        axisXLabel.setFillColor(sf::Color::Black);

        sf::Vector2f labelOrigin(axisXLabel.getLocalBounds().width / 2.f, 0);
        posX.y += labelIndent;
        axisXLabel.setOrigin(labelOrigin);
        axisXLabel.setPosition(posX);

        posX.y -= labelIndent;
        posX.y -= _absCenter.y;
        posY.x -= _absCenter.x;

        sf::RectangleShape vertical(sf::Vector2f(1, _size.y)),
            horizontal(sf::Vector2f(_size.x, 1));
        vertical.setPosition(posX);
        vertical.setFillColor(verticalColor);
        vertical.setOutlineThickness(1.f);
        vertical.setOutlineColor(bigShadow);
        
        horizontal.setPosition(posY);
        horizontal.setFillColor(horizontalColor);
        horizontal.setOutlineThickness(1.f);
        horizontal.setOutlineColor(bigShadow);

        _target->draw(vertical);
        _target->draw(horizontal);
        _target->draw(axisXLabel);
    }
}

void GraphScene::drawAxes() {
    const sf::Color shadow = sf::Color(0, 0, 0, 40);

    sf::RectangleShape axisX(sf::Vector2f(_size.x, GRAPH_AXIS_WIDTH)),
        axisY(sf::Vector2f(GRAPH_AXIS_WIDTH, _size.y));

    axisX.setFillColor(sf::Color::Black);
    axisX.setOutlineThickness(1.f);
    axisX.setOutlineColor(shadow);
    axisY.setFillColor(sf::Color::Black);
    axisY.setOutlineThickness(1.f);
    axisY.setOutlineColor(shadow);

    axisX.setOrigin(axisX.getSize() / 2.f);
    axisY.setOrigin(axisY.getSize() / 2.f);
    axisX.setPosition(_absOrigin);
    axisY.setPosition(_absOrigin);

    _target->draw(axisX);
    _target->draw(axisY);
}

void GraphScene::drawAxesLabels() {
    sf::Text textX("x", _axisFont, 14), textY("y", _axisFont, 12);
    textX.setPosition(absoluteCoords(_scale, 0) + sf::Vector2f(-12.f, 5.f));
    textY.setPosition(absoluteCoords(0, _scale) + sf::Vector2f(10.f, 0.f));
    textX.setStyle(sf::Text::Bold);
    textY.setStyle(sf::Text::Bold);
    textX.setFillColor(sf::Color::Black);
    textY.setFillColor(sf::Color::Black);
    _target->draw(textX);
    _target->draw(textY);

    const float radius = 10.f;
    sf::CircleShape arrow(radius, 3);
    arrow.setOrigin(radius, 0);
    arrow.setPosition(absoluteCoords(0, _scale));
    arrow.setFillColor(sf::Color::Black);
    _target->draw(arrow);

    arrow.rotate(90.f);
    arrow.setFillColor(sf::Color::Black);
    arrow.setPosition(absoluteCoords(_scale, 0));
    _target->draw(arrow);
}

void GraphScene::drawFunc(const sf::Color &color,
                          std::function<float(float)> func) {
    sf::Vector2f lastPosition;
    float step = _scale / 100.f;

    FuncDirection direction = CONTINUOUS;
    FuncDirection lastDirection = CONTINUOUS;
    std::size_t dirLasted = 0;

    for (float x = -_scale - 1.f; x < _scale + 2.f * step; x += step) {
        float y = func(x);
        sf::Vector2f position = absoluteCoords(x, y);
        if (x == -_scale) {
            lastPosition = position;
            continue;
        }

        FuncDirection currDirection;
        currDirection = lastPosition.y < position.y ? DESCENDING : ASCENDING;
        bool switched = direction != CONTINUOUS && currDirection != direction;
        bool spike = std::abs(position.y - lastPosition.y) > 1000.f;
        if (switched && spike) {
            dirLasted = 0;
            direction = CONTINUOUS;
            lastPosition = position;
            continue;
        }

        if (lastDirection == currDirection)
            dirLasted++;
        if (dirLasted > 10)
            direction = currDirection;

        Line segment(lastPosition, position, GRAPH_AXIS_WIDTH);
        segment.setFillColor(color);
        segment.setOutlineColor(sf::Color(0, 0, 0, 10));
        segment.setOutlineThickness(1.f);

        _target->draw(segment);
        lastPosition = position;
        lastDirection = currDirection;
    }
}

bool GraphScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter ||
            event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Space) {
            _finishing = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Project0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        _scale += event.mouseWheelScroll.delta;
    }
    return true;
}

sf::Vector2f GraphScene::absoluteCoords(float x, float y) {
    sf::Vector2f position(_absOrigin.x + _absCenter.x * x / _scale,
            _absOrigin.y - _absCenter.y * y / _scale);
    return position;
}

sf::Vector2f GraphScene::absoluteCoords(const sf::Vector2f &relative) {
    return absoluteCoords(relative.x, relative.y);
}
