#include "menuscene.h"

#include <cmath>

#include "fragrect.hpp"
#include "resources.hpp"

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    _colorOffset = 0.f;

    sf::Vector2f size(400.f, 280.f);
    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.f);
    _background.setPosition(_target->getSize().x / 2.f,
                            _target->getSize().y / 2.f);

    const std::string vertexSource = RESOURCE(border_vert);
    _borderShader.loadFromMemory(vertexSource, sf::Shader::Vertex);
    _borderShader.setUniform("off", _colorOffset);
}

void MenuScene::update(sf::Time elapsed) {}

void MenuScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color(6, 12, 8));
    _target->draw(_background);

    sf::Vector2f center = _background.getPosition();
    sf::Vector2f size = _background.getSize();

    float margin = 10.f;
    float thickness = 5.f;

    FragmentRectangleShape r1(sf::Vector2f(size.x - 2.f * margin, thickness), 10, 1);
    r1.setFillColor(sf::Color::White);
    r1.setOrigin(r1.getSize().x / 2.f, 0.f);
    r1.setPosition(center.x, center.y - size.y / 2.f + margin);

    FragmentRectangleShape r2(sf::Vector2f(size.x - 2.f * margin, thickness), 10, 1);
    r2.setFillColor(sf::Color::White);
    r2.setOrigin(r2.getSize().x / 2.f, r2.getSize().y);
    r2.setPosition(center.x, center.y + size.y / 2.f - margin);

    FragmentRectangleShape r3(sf::Vector2f(thickness, size.y - 2.f * margin), 1, 10);
    r3.setFillColor(sf::Color::White);
    r3.setOrigin(r3.getSize().x, r3.getSize().y / 2.f);
    r3.setPosition(center.x + size.x / 2.f - margin, center.y);

    FragmentRectangleShape r4(sf::Vector2f(thickness, size.y - 2.f * margin), 1, 10);
    r4.setFillColor(sf::Color::White);
    r4.setOrigin(r4.getSize().x - thickness, r4.getSize().y / 2.f);
    r4.setPosition(center.x - size.x / 2.f + margin, center.y);

    _target->draw(r1, &_borderShader);
    _target->draw(r2, &_borderShader);
    _target->draw(r3, &_borderShader);
    _target->draw(r4, &_borderShader);

    _colorOffset += 0.0001f;
    if (_colorOffset > 2.f * M_PI)
        _colorOffset = 0.f;
    _borderShader.setUniform("off", _colorOffset);
}

bool MenuScene::handleEvent(const sf::Event &event) { return true; }
