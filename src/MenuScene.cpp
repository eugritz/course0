#include "MenuScene.h"

#include <cmath>
#include <iostream>

#include "FragmentRectangleShape.h"
#include "Course0.h"
#include "Resources.hpp"

const float margin = MENU_BORDER_MARGIN;
const float width = MENU_BORDER_WIDTH;

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    _colorOffsetTimeout = 0;
    _colorOffset = 0.f;
    _nextCharTimeout = 0;
    _loadingDuration = 0;
    _loadingFinished = false;
}

void MenuScene::setup(std::size_t cols, std::size_t rows) {
    const std::string vertexSource = BINARY_RESOURCE(border_vert);
    _borderShader.loadFromMemory(vertexSource, sf::Shader::Vertex);
    _borderShader.setUniform("off", _colorOffset);

    if (!_itemFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
        return;
    }
    _itemFont.setSmooth(true);

    float characterWidth = _itemFont.getGlyph('A',
            MENU_ITEM_FONT_SIZE, false, 0).bounds.width;
    float menuWidth = characterWidth * cols;

    sf::Vector2f center(_target->getSize().x / 2.f,
                        _target->getSize().y / 2.f);
    setupMenu(menuWidth, rows, center);
    sf::Vector2f size(menuWidth, _menu.getSize().y + margin * 4.f);
    setupBorders(size, center);

    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.f);
    _background.setPosition(center);
}

void MenuScene::setup(const sf::Vector2f &size) {
    if (!_itemFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
        return;
    }
    _itemFont.setSmooth(true);

    float characterWidth = _itemFont.getGlyph('A',
            MENU_ITEM_FONT_SIZE, false, 0).bounds.width;

    sf::Vector2f center(_target->getSize().x / 2.f,
                        _target->getSize().y / 2.f);
    setupMenuRaw(size.x, size.y, center);
    sf::Vector2f sizeMargins(size.x + 4.f * margin, _menu.getSize().y + margin * 4.f);
    setupBorders(sizeMargins, center);

    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.f);
    _background.setPosition(center);
}

void MenuScene::setupBorders(const sf::Vector2f &size,
                             const sf::Vector2f &center) {
    const std::string vertexSource = BINARY_RESOURCE(border_vert);
    _borderShader.loadFromMemory(vertexSource, sf::Shader::Vertex);
    _borderShader.setUniform("off", _colorOffset);

    _r1.setSize(sf::Vector2f(size.x - 2.f * margin, width));
    _r1.setFragments(10, 1);
    _r1.setFillColor(sf::Color::White);
    _r1.setOrigin(_r1.getSize().x / 2.f, 0.f);
    _r1.setPosition(center.x, center.y - size.y / 2.f + margin);

    _r2.setSize(sf::Vector2f(size.x - 2.f * margin, width));
    _r2.setFragments(10, 1);
    _r2.setFillColor(sf::Color::White);
    _r2.setOrigin(_r2.getSize().x / 2.f, _r2.getSize().y);
    _r2.setPosition(center.x, center.y + size.y / 2.f - margin);

    _r3.setSize(sf::Vector2f(width, size.y - 2.f * margin));
    _r3.setFragments(1, 10);
    _r3.setFillColor(sf::Color::White);
    _r3.setOrigin(_r3.getSize().x, _r3.getSize().y / 2.f);
    _r3.setPosition(center.x + size.x / 2.f - margin, center.y);

    _r4.setSize(sf::Vector2f(width, size.y - 2.f * margin));
    _r4.setFragments(1, 10);
    _r4.setFillColor(sf::Color::White);
    _r4.setOrigin(_r4.getSize().x - width, _r4.getSize().y / 2.f);
    _r4.setPosition(center.x - size.x / 2.f + margin, center.y);
}

bool MenuScene::setupMenu(float menuWidth, std::size_t rows,
                          const sf::Vector2f &center) {
    _menu.create(rows, _itemFont, MENU_ITEM_FONT_SIZE);
    _menu.setIndent(MENU_ITEM_INDENT);
    menuWidth = std::floor(menuWidth);
    if ((long)menuWidth % 2 != 0)
        menuWidth = std::floor(menuWidth - 1.f);

    sf::Vector2f menuSize = _menu.getSize();
    menuSize = _menu.setFixedSize(sf::Vector2f(
        menuWidth - margin * 2.f - width * 4.f,
        menuSize.y
    ));
    _menu.setOrigin(menuSize / 2.f);
    _menu.setPosition(center);
    return true;
}

bool MenuScene::setupMenuRaw(float menuWidth, float menuHeight,
                          const sf::Vector2f &center) {
    _menu.create(_itemFont, MENU_ITEM_FONT_SIZE);
    _menu.setIndent(MENU_ITEM_INDENT);
    menuWidth = std::floor(menuWidth);
    if ((long)menuWidth % 2 != 0)
        menuWidth = std::floor(menuWidth - 1.f);

    sf::Vector2f menuSize = _menu.getSize();
    menuSize = _menu.setFixedSize(sf::Vector2f(
        menuWidth - margin * 2.f - width * 4.f,
        menuHeight
    ));
    _menu.setOrigin(menuSize / 2.f);
    _menu.setPosition(center);
    return true;
}

void MenuScene::update(sf::Time elapsed) {
    std::size_t totalLength = _menu.getTotalLength();
    if (totalLength != 0 && !_loadingFinished) {
        int timeout = MENU_LOADING_DURATION / totalLength;
        while (_nextCharTimeout > timeout) {
            _nextCharTimeout -= timeout;
            _menu.update();
        }
    }

    if ((!_loadingFinished && _loadingDuration >= MENU_LOADING_DURATION) ||
            totalLength == 0) {
        _menu.setAnimationFinished(true);
        _loadingFinished = true;
    }

    if (_colorOffset > 2.f * M_PI)
        _colorOffset = 0.f;
    if (_colorOffsetTimeout > MENU_COLOR_OFFSET_TIMEOUT) {
        _colorOffsetTimeout = 0;
        _colorOffset += MENU_COLOR_OFFSET_STEP;
        _borderShader.setUniform("off", _colorOffset);
    }

    _colorOffsetTimeout += elapsed.asMicroseconds();
    _nextCharTimeout += elapsed.asMicroseconds();
    _loadingDuration += elapsed.asMicroseconds();
}

void MenuScene::draw(sf::RenderStates states) {
    _target->clear(sf::Color(6, 12, 8));
    _target->draw(_background);

    _target->draw(_r1, &_borderShader);
    _target->draw(_r2, &_borderShader);
    _target->draw(_r3, &_borderShader);
    _target->draw(_r4, &_borderShader);

    _target->draw(_menu);
}

bool MenuScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (!_loadingFinished) {
            _menu.setAnimationFinished(true);
            _loadingFinished = true;
            return false;
        }
    }
    return true;
}
