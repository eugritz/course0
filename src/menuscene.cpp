#include "menuscene.h"

#include <cmath>

#include "fragrect.hpp"
#include "resources.hpp"

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    _colorOffset = 0.f;

    const std::string vertexSource = RESOURCE(border_vert);
    _borderShader.loadFromMemory(vertexSource, sf::Shader::Vertex);
    _borderShader.setUniform("off", _colorOffset);

    float margin = 10.f;
    float thickness = 5.f;

    sf::Vector2f size(400.f, 280.f);
    sf::Vector2f center(_target->getSize().x / 2.f,
                        _target->getSize().y / 2.f);
    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.f);
    _background.setPosition(center);

    _r1.setSize(sf::Vector2f(size.x - 2.f * margin, thickness));
    _r1.setFragments(10, 1);
    _r1.setFillColor(sf::Color::White);
    _r1.setOrigin(_r1.getSize().x / 2.f, 0.f);
    _r1.setPosition(center.x, center.y - size.y / 2.f + margin);

    _r2.setSize(sf::Vector2f(size.x - 2.f * margin, thickness));
    _r2.setFragments(10, 1);
    _r2.setFillColor(sf::Color::White);
    _r2.setOrigin(_r2.getSize().x / 2.f, _r2.getSize().y);
    _r2.setPosition(center.x, center.y + size.y / 2.f - margin);

    _r3.setSize(sf::Vector2f(thickness, size.y - 2.f * margin));
    _r3.setFragments(1, 10);
    _r3.setFillColor(sf::Color::White);
    _r3.setOrigin(_r3.getSize().x, _r3.getSize().y / 2.f);
    _r3.setPosition(center.x + size.x / 2.f - margin, center.y);

    _r4.setSize(sf::Vector2f(thickness, size.y - 2.f * margin));
    _r4.setFragments(1, 10);
    _r4.setFillColor(sf::Color::White);
    _r4.setOrigin(_r4.getSize().x - thickness, _r4.getSize().y / 2.f);
    _r4.setPosition(center.x - size.x / 2.f + margin, center.y);
}

void MenuScene::update(sf::Time elapsed) {
    if (_colorOffset > 2.f * M_PI)
        _colorOffset = 0.f;
    if (elapsed.asMicroseconds() > MENU_COLOR_OFFSET_TIMEOUT) {
        _colorOffset += 0.0001f;
        _borderShader.setUniform("off", _colorOffset);
    }
}

void MenuScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color(6, 12, 8));
    _target->draw(_background);

    _target->draw(_r1, &_borderShader);
    _target->draw(_r2, &_borderShader);
    _target->draw(_r3, &_borderShader);
    _target->draw(_r4, &_borderShader);
}

bool MenuScene::handleEvent(const sf::Event &event) { return true; }
