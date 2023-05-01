#include "GraphScene.h"

#include <cmath>
#include <iostream>

#include "Course0.h"

float clamp(float val, float min, float max);
std::string to_string_rounded(float val, std::size_t precision);

const sf::Color firstColor = sf::Color(210, 80, 60);
const sf::Color secondColor = sf::Color(70, 70, 190);

float first(float x) {
    return 1.f / std::tan(x);
}

float second(float x) {
    return std::pow(2.f, x)*std::log10(x) - std::pow(3.f, x)*std::log10(x);
}

GraphScene::GraphScene(sf::RenderTarget *target) : Scene(target) {
    _size = target->getSize();
    _graph.create(_size);

    _finishing = false;
    _grab = false;

    if (!_axisFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
    }

    _graph.add({ firstColor, first });
    _graph.add({ secondColor, second });
}

void GraphScene::update(sf::Time elapsed) {
    _graph.update();
}

void GraphScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color::White);
    drawAxes();
    drawGrid();
    drawFunc();
    drawAxesLabels();

    sf::Text firstLabel("y=ctg(x)", _axisFont, 10);
    firstLabel.setOutlineThickness(2.f);
    firstLabel.setOutlineColor(sf::Color::White);
    firstLabel.setFillColor(firstColor);
    firstLabel.setPosition(_graph.absoluteCoords(0.6f, first(0.8f)));
    firstLabel.setStyle(sf::Text::Bold);

    sf::Text secondLabel("y=2^x*log(x)-3^x*log(x)", _axisFont, 10);
    secondLabel.setOutlineThickness(2.f);
    secondLabel.setOutlineColor(sf::Color::White);
    secondLabel.setFillColor(secondColor);
    secondLabel.setPosition(_graph.absoluteCoords(0.3f, -0.9));
    secondLabel.setStyle(sf::Text::Bold);

    _target->draw(firstLabel);
    _target->draw(secondLabel);
}

void GraphScene::drawGrid() {
    const float step = _size.x / 20.f;
    const sf::Color verticalColor = sf::Color(0, 0, 0, 30);
    const sf::Color horizontalColor = sf::Color(0, 0, 0, 40);
    const sf::Color bigShadow = sf::Color(0, 0, 0, 5);

    float remX = std::remainder(_graph.getOrigin().x, step);
    float remY = std::remainder(_graph.getOrigin().y, step);
    for (float x = remX, y = remY; x < _size.x; x += step, y += step) {
        sf::Vector2f posX(x, 0.f), posY(0, y);
        float roundedX = std::round(_graph.relativeCoords(x, 0).x * 100.f) / 100.f;
        float roundedY = std::round(_graph.relativeCoords(0, y).y * 100.f) / 100.f;
        std::string labelX = to_string_rounded(roundedX, 2);
        std::string labelY = to_string_rounded(roundedY, 2);

        sf::Text labelText(labelX, _axisFont, GRAPH_AXIS_VALUES_FONT_SIZE);
        labelText.setOutlineThickness(GRAPH_LABEL_THICKNESS);
        labelText.setOutlineColor(sf::Color::White);
        labelText.setFillColor(sf::Color::Black);

        sf::FloatRect bounds = labelText.getLocalBounds();
        labelText.setOrigin(bounds.width / 2.f, -GRAPH_AXIS_VALUES_INDENT);
        labelText.setPosition(posX.x, clamp(_graph.getOrigin().y,
                    0.f, _size.y - 2.f * bounds.height));
        _target->draw(labelText);

        if (roundedY != 0.f) {
            labelText.setString(labelY);
            bounds = labelText.getLocalBounds();
            labelText.setOrigin(bounds.width, bounds.height / 2.f);
            labelText.setPosition(clamp(_graph.getOrigin().x,
                        bounds.width + 5.f, _size.x - 5.f), posY.y);
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
    axisX.setPosition(_graph.getCenter().x, _graph.getOrigin().y);
    axisY.setPosition(_graph.getOrigin().x, _graph.getCenter().y);

    _target->draw(axisX);
    _target->draw(axisY);
}

void GraphScene::drawAxesLabels() {
    sf::Text textX("x", _axisFont, GRAPH_AXIS_LABEL_FONT_SIZE),
        textY("y", _axisFont, GRAPH_AXIS_LABEL_FONT_SIZE);
    sf::FloatRect boundsX = textX.getLocalBounds();
    sf::FloatRect boundsY = textY.getLocalBounds();

    textX.setPosition(_size.x - 12.f, clamp(_graph.getOrigin().y + 5.f,
                12.f, _size.y - 3.f * boundsX.height));
    textY.setPosition(clamp(_graph.getOrigin().x + 10.f,
                10.f, _size.x - 3.f * boundsY.width), 2.f);

    textX.setOutlineThickness(GRAPH_LABEL_THICKNESS);
    textY.setOutlineThickness(GRAPH_LABEL_THICKNESS);
    textX.setOutlineColor(sf::Color::White);
    textY.setOutlineColor(sf::Color::White);
    textX.setFillColor(sf::Color::Black);
    textY.setFillColor(sf::Color::Black);

    textY.setStyle(sf::Text::Bold);
    textX.setStyle(sf::Text::Bold);
    _target->draw(textX);
    _target->draw(textY);

    const float radius = GRAPH_AXIS_ARROW_RADIUS;
    sf::CircleShape arrow(radius, 3);
    arrow.setOrigin(radius, 0);
    arrow.setPosition(clamp(_graph.getOrigin().x, 0.f, _size.x), 0);
    arrow.setFillColor(sf::Color::Black);
    _target->draw(arrow);

    arrow.rotate(90.f);
    arrow.setFillColor(sf::Color::Black);
    arrow.setPosition(_size.x, clamp(_graph.getOrigin().y, 0.f, _size.y));
    _target->draw(arrow);
}

void GraphScene::drawFunc() {
    _target->draw(_graph);
}

bool GraphScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    } else if (event.type == sf::Event::MouseMoved) {
        onMouseMoved(event.mouseMove);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        onMouseButtonPressed(event.mouseButton);
    } else if (event.type == sf::Event::MouseButtonReleased) {
        onMouseButtonReleased(event.mouseButton);
    } else if (event.type == sf::Event::MouseWheelScrolled) {
        onMouseWheelScrolled(event.mouseWheelScroll);
    }
    return true;
}

void GraphScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Enter ||
        event.code == sf::Keyboard::Escape ||
        event.code == sf::Keyboard::Space) {
        _finishing = true;
    } else if (event.code == sf::Keyboard::Left) {
        _graph.move(10.f, 0);
    } else if (event.code == sf::Keyboard::Right) {
        _graph.move(-10.f, 0);
    } else if (event.code == sf::Keyboard::Up) {
        _graph.move(0, 10.f);
    } else if (event.code == sf::Keyboard::Down) {
        _graph.move(0, -10.f);
    } else if (event.code == sf::Keyboard::Add ||
            (event.shift && event.code == sf::Keyboard::Equal)) {
        _graph.scale(1.f);
    } else if (event.code == sf::Keyboard::Subtract ||
            event.code == sf::Keyboard::Hyphen) {
        _graph.scale(-1.f);
    } else if (event.code == sf::Keyboard::Home) {
        _graph.origin();
    }
}

void GraphScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        Course0::getInstance()->postEvent(MENU_OPEN);
        _finishing = false;
    }
}

void GraphScene::onMouseMoved(const sf::Event::MouseMoveEvent &event) {
    if (_grab) {
        float x = event.x, y = event.y;

        float dx = x - _cursorPosition.x;
        float dy = y - _cursorPosition.y;
        _graph.move(dx, dy);

        _cursorPosition.x = x;
        _cursorPosition.y = y;
    }
}

void GraphScene::onMouseButtonPressed(
        const sf::Event::MouseButtonEvent &event) {
    if (event.button == sf::Mouse::Left) {
        _cursorPosition.x = event.x;
        _cursorPosition.y = event.y;
        _grab = true;
    }
}

void GraphScene::onMouseButtonReleased(
        const sf::Event::MouseButtonEvent &event) {
    if (_grab && event.button == sf::Mouse::Left)
        _grab = false;
}

void GraphScene::onMouseWheelScrolled(
        const sf::Event::MouseWheelScrollEvent &event) {
    _graph.scale(event.delta);
}

float clamp(float val, float min, float max) {
    if (val < min) return min;
    else if (val > max) return max;
    else return val;
}

std::string to_string_rounded(float val, std::size_t precision) {
    std::string s = std::to_string(val);
    if (s.find_first_of("123456789") == s.npos && s[0] == '-')
        s = s.substr(1);
    std::size_t point = s.find('.');
    if (point != s.npos) {
        while (s.back() == '0')
            s.pop_back();
        while (s.back() == '.')
            s.pop_back();
    }
    return s.substr(0, point + precision + 1);
}
