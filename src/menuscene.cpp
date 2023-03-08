#include "menuscene.h"

#include "fragrect.hpp"

sf::Shader _shader;
float _off;

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2f size(400.0, 280.0);
    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.0f);
    _background.setPosition(_target->getSize().x / 2.0,
                            _target->getSize().y / 2.0);

    const std::string vertexShader = \
    "uniform float off;"
    "void main() {" \
    "    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
    "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" \
    "    gl_FrontColor = vec4(cos(gl_Position.x+1.0+off)," \
    "                         cos(gl_Position.x+off)," \
    "                         cos(gl_Position.x-1.0+off)," \
    "                         1.0);" \
    "}";
    _shader.loadFromMemory(vertexShader, sf::Shader::Vertex);
    _shader.setUniform("off", _off);
}

void MenuScene::update(sf::Time elapsed) {}

void MenuScene::draw(sf::RenderStates states) const {
    _target->clear(sf::Color(6, 12, 8));
    _target->draw(_background);

    sf::Vector2f center = _background.getPosition();
    sf::Vector2f size = _background.getSize();

    float margin = 10.0f;
    float thickness = 5.0f;

    FragmentRectangleShape r1(sf::Vector2f(size.x - 2.f * margin, thickness), 2, 1);
    r1.setFillColor(sf::Color::White);
    r1.setOrigin(r1.getSize().x / 2.f, 0.f);
    r1.setPosition(center.x, center.y - size.y / 2.f + margin);

    FragmentRectangleShape r2(sf::Vector2f(size.x - 2.f * margin, thickness), 2, 1);
    r2.setFillColor(sf::Color::White);
    r2.setOrigin(r2.getSize().x / 2.f, r2.getSize().y);
    r2.setPosition(center.x, center.y + size.y / 2.f - margin);

    FragmentRectangleShape r3(sf::Vector2f(thickness, size.y - 2.f * margin), 1, 2);
    r3.setFillColor(sf::Color::White);
    r3.setOrigin(r3.getSize().x, r3.getSize().y / 2.f);
    r3.setPosition(center.x + size.x / 2.f - margin, center.y);

    FragmentRectangleShape r4(sf::Vector2f(thickness, size.y - 2.f * margin), 1, 2);
    r4.setFillColor(sf::Color::White);
    r4.setOrigin(r4.getSize().x - thickness, r4.getSize().y / 2.f);
    r4.setPosition(center.x - size.x / 2.f + margin, center.y);

    _target->draw(r1, &_shader);
    _target->draw(r2, &_shader);
    _target->draw(r3, &_shader);
    _target->draw(r4, &_shader);

    _off += 0.0001f;
    _shader.setUniform("off", _off);
}

bool MenuScene::handleEvent(const sf::Event &event) { return true; }
