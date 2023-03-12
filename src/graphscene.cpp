#include "graphscene.h"

#include <cmath>
#include <iostream>

#include "line.hpp"
#include "project0.h"

std::string to_string_rounded(float val);

const sf::Color firstColor = sf::Color(190, 80, 60);
const sf::Color secondColor = sf::Color(70, 70, 180);

float first(float x) {
    return 1.f / tan(x);
}

float second(float x) {
    return std::pow(2.f, x)*std::log10(x) - std::pow(3.f, x)*std::log10(x);
}

GraphScene::GraphScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2u size = target->getSize();
    _size.x = size.x;
    _size.y = size.y;
    _absCenter.x = size.x / 2.f;
    _absCenter.y = size.y / 2.f;
    _absOrigin = _absCenter;
    _finishing = false;
    _scale = 10.f;

    if (!_axisFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
    }

}

void GraphScene::update(sf::Time elapsed) { }

void GraphScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color::White);
    drawAxes();
    drawGrid();

    drawFunc(firstColor, first);
    drawFunc(secondColor, second);

    drawAxesLabels();

    sf::Text firstLabel("y=ctg(x)", _axisFont, 10);
    firstLabel.setOutlineThickness(2.f);
    firstLabel.setOutlineColor(sf::Color::White);
    firstLabel.setFillColor(firstColor);
    firstLabel.setPosition(absoluteCoords(0.6f, first(0.8f)));
    firstLabel.setStyle(sf::Text::Bold);

    sf::Text secondLabel("y=2^x*log(x)-3^x*log(x)", _axisFont, 10);
    secondLabel.setOutlineThickness(2.f);
    secondLabel.setOutlineColor(sf::Color::White);
    secondLabel.setFillColor(secondColor);
    secondLabel.setPosition(absoluteCoords(0.3f, -0.9));
    secondLabel.setStyle(sf::Text::Bold);

    _target->draw(firstLabel);
    _target->draw(secondLabel); }

void GraphScene::drawGrid() {
    const float step = _size.x / 20.f;
    const sf::Color verticalColor = sf::Color(0, 0, 0, 30);
    const sf::Color horizontalColor = sf::Color(0, 0, 0, 40);
    const sf::Color bigShadow = sf::Color(0, 0, 0, 5);

    float remX = std::remainder(_absOrigin.x, step);
    float remY = std::remainder(_absOrigin.y, step);
    for (float x = remX, y = remY; x < _size.x; x += step, y += step) {
        sf::Vector2f posX(x, 0.f), posY(0, y);

        float roundedX = std::round(relativeCoords(x, 0).x * 100.f) / 100.f;
        float roundedY = std::round(relativeCoords(0, y).y * 100.f) / 100.f;
        std::string labelX = to_string_rounded(roundedX);
        std::string labelY = to_string_rounded(roundedY);

        sf::Text labelText(labelX, _axisFont, GRAPH_AXIS_VALUES_FONT_SIZE);
        labelText.setOutlineThickness(2.f);
        labelText.setOutlineColor(sf::Color::White);
        labelText.setFillColor(sf::Color::Black);

        sf::FloatRect bounds = labelText.getLocalBounds();
        labelText.setOrigin(bounds.width / 2.f, -GRAPH_AXIS_VALUES_INDENT);
        labelText.setPosition(posX.x, _absOrigin.y);
        _target->draw(labelText);

        if (roundedY != 0.f) {
            labelText.setString(labelY);
            bounds = labelText.getLocalBounds();
            labelText.setOrigin(bounds.width, bounds.height / 2.f);
            labelText.setPosition(_absOrigin.x, posY.y);
            _target->draw(labelText);
        }

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
    axisX.setPosition(_absCenter.x, _absOrigin.y);
    axisY.setPosition(_absOrigin.x, _absCenter.y);

    _target->draw(axisX);
    _target->draw(axisY);
}

void GraphScene::drawAxesLabels() {
    sf::Text textX("x", _axisFont, 14), textY("y", _axisFont, 12);
    textX.setPosition(_size.x - 12.f, _absOrigin.y + 5.f);
    textY.setPosition(_absOrigin.x + 10.f, 0.f);

    textX.setOutlineThickness(2.f);
    textY.setOutlineThickness(2.f);

    textX.setOutlineColor(sf::Color::White);
    textY.setOutlineColor(sf::Color::White);

    textX.setFillColor(sf::Color::Black);
    textY.setFillColor(sf::Color::Black);

    textX.setStyle(sf::Text::Bold);
    textY.setStyle(sf::Text::Bold);

    _target->draw(textX);
    _target->draw(textY);

    const float radius = 10.f;
    sf::CircleShape arrow(radius, 3);
    arrow.setOrigin(radius, 0);
    arrow.setPosition(_absOrigin.x, 0);
    arrow.setFillColor(sf::Color::Black);
    _target->draw(arrow);

    arrow.rotate(90.f);
    arrow.setFillColor(sf::Color::Black);
    arrow.setPosition(_size.x, _absOrigin.y);
    _target->draw(arrow);
}

void GraphScene::drawFunc(const sf::Color &color,
                          std::function<float(float)> func) {
    const float step = _scale / 100.f;
    const float tinyStep = step / 10.f;

    const float start = relativeCoords(0, 0).x - _scale / 10.f;
    const float end = relativeCoords(_size.x, 0).x + _scale / 10.f;

    FuncDirection direction = CONTINUOUS;
    sf::Vector2f position = absoluteCoords(start, func(start));

    bool jump = false;
    std::size_t dirLasted = 0;
    FuncDirection funcDirection = CONTINUOUS;

    auto jumped = [&](const sf::Vector2f &pos, FuncDirection dir) {
        bool switched = funcDirection != CONTINUOUS && dir != funcDirection;
        bool spike = std::abs(pos.y - position.y) > GRAPH_SPIKE_DIFF;
        return switched && spike;
    };

    for (float x = start + step; x < end; x += step) {
        float y = func(x);
        sf::Vector2f nextPosition = absoluteCoords(x, y);
        FuncDirection nextDirection;
        nextDirection = position.y < nextPosition.y ? DESCENDING : ASCENDING;

        jump = !jump && jumped(nextPosition, nextDirection);
        if (direction == nextDirection)
            dirLasted++;
        if (!jump && dirLasted > _scale)
            funcDirection = nextDirection;

        Line segment(2.f);
        if (jump) {
            float localX = x - step + tinyStep;
            float localY = func(localX);
            sf::Vector2f pos = absoluteCoords(localX, localY);
            FuncDirection dir = position.y < pos.y ? DESCENDING : ASCENDING;
            if (jumped(pos, dir)) {
                position = nextPosition;
                continue;
            } else {
                segment.setPoints(position, pos);
                dirLasted = 0;
                funcDirection = CONTINUOUS;
            }
        } else {
            segment.setPoints(position, nextPosition);
        }
        segment.setFillColor(color);
        segment.setOutlineColor(sf::Color(0, 0, 0, 10));
        segment.setOutlineThickness(1.f);
        _target->draw(segment);

        direction = nextDirection;
        position = nextPosition;
    }
}

void GraphScene::scale(float delta) {
    if (1.f <= _scale - delta && _scale - delta <= 10.f) {
        _scale -= delta;
    }
}

bool GraphScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter ||
            event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Space) {
            _finishing = true;
        } else if (event.key.code == sf::Keyboard::Left) {
            _absOrigin.x += 10.f;
        } else if (event.key.code == sf::Keyboard::Right) {
            _absOrigin.x -= 10.f;
        } else if (event.key.code == sf::Keyboard::Up) {
            _absOrigin.y += 10.f;
        } else if (event.key.code == sf::Keyboard::Down) {
            _absOrigin.y -= 10.f;
        } else if (event.key.code == sf::Keyboard::Add ||
                (event.key.shift && event.key.code == sf::Keyboard::Equal)) {
            scale(1.f);
        } else if (event.key.code == sf::Keyboard::Subtract ||
                event.key.code == sf::Keyboard::Hyphen) {
            scale(-1.f);
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Project0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        scale(-event.mouseWheelScroll.delta);
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

sf::Vector2f GraphScene::relativeCoords(float x, float y) {
    sf::Vector2f position((x - _absOrigin.x) * _scale / _absCenter.x,
            (y - _absOrigin.y) * _scale / _absCenter.y);
    return position;
}

sf::Vector2f GraphScene::relativeCoords(const sf::Vector2f &absolute) {
    return relativeCoords(absolute.x, absolute.y);
}

std::string to_string_rounded(float val) {
    std::string s = std::to_string(val);
    if (s.find_first_of("123456789") == s.npos && s[0] == '-')
        s = s.substr(1);
    while (s.back() == '0')
        s.pop_back();
    while (s.back() == '.')
        s.pop_back();
    return s;
}
