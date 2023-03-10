#include "menuscene.h"

#include <cmath>
#include <iostream>

#include "fragrect.hpp"
#include "resources.hpp"

const float margin = MENU_BORDER_MARGIN;
const float width = MENU_BORDER_WIDTH;

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    _colorOffsetTimeout = 0;
    _colorOffset = 0.f;

    _inputBlinking = false;
    _inputBlinkingSwitch = false;
    _inputBlinkingTimeout = 0;
    _inputControl = false;
    _inputAlt = false;

    const std::string vertexSource = RESOURCE(border_vert);
    _borderShader.loadFromMemory(vertexSource, sf::Shader::Vertex);
    _borderShader.setUniform("off", _colorOffset);

    sf::Vector2f size(400.f, 280.f);
    sf::Vector2f center(_target->getSize().x / 2.f,
                        _target->getSize().y / 2.f);
    _background.setFillColor(sf::Color::Black);
    _background.setSize(size);
    _background.setOrigin(size / 2.f);
    _background.setPosition(center);

    setupBorders(size, center);
    setupMenu(size, center);
}

void MenuScene::update(sf::Time elapsed) {
    if (_colorOffset > 2.f * M_PI)
        _colorOffset = 0.f;
    if (_colorOffsetTimeout > MENU_COLOR_OFFSET_TIMEOUT) {
        _colorOffsetTimeout = 0;
        _colorOffset += MENU_COLOR_OFFSET_STEP;
        _borderShader.setUniform("off", _colorOffset);
    }

    if (_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _menu[INPUT].getString();
        _menu[INPUT].setString(input + "_");
        _inputBlinkingSwitch = false;
    } else if (!_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _menu[INPUT].getString();
        _menu[INPUT].setString(input.substring(0, input.getSize() - 1));
        _inputBlinkingSwitch = false;
    }

    if (_inputBlinkingTimeout > MENU_INPUT_BLINKING_TIMEOUT) {
        _inputBlinkingTimeout = 0;
        _inputBlinking = !_inputBlinking;
        _inputBlinkingSwitch = true;
    }

    _colorOffsetTimeout += elapsed.asMicroseconds();
    _inputBlinkingTimeout += elapsed.asMicroseconds();
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
    bool blocked = _inputControl || _inputAlt;

    if (!blocked && event.type == sf::Event::TextEntered) {
        sf::String input = _menu[INPUT].getString();
        if (event.text.unicode == 8) {
            _input = _input.substring(0, _input.getSize() - 1);
        } else if (event.text.unicode > 31) {
            _input += event.text.unicode;
        } else {
            return true;
        }

        _menu[INPUT].setString(PROMPT + _input);
        _inputBlinkingTimeout = 0;
        _inputBlinking = false;
        interactiveInput();
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.control)
            _inputControl = true;
        else if (event.key.alt)
            _inputAlt = true;
    } else if (event.type == sf::Event::KeyReleased) {
        if (event.key.control)
            _inputControl = false;
        else if (event.key.alt)
            _inputAlt = false;
    }
    return true;
}

void MenuScene::interactiveInput() {
    _menu[INTRO].setStyle(sf::Text::Regular);
    _menu[GRAPH].setStyle(sf::Text::Regular);
    _menu[AUTHOR].setStyle(sf::Text::Regular);

    if (_input == "1") {
        _menu[INTRO].setStyle(sf::Text::Underlined);
    } else if (_input == "2") {
        _menu[GRAPH].setStyle(sf::Text::Underlined);
    } else if (_input == "3") {
        _menu[AUTHOR].setStyle(sf::Text::Underlined);
    }
}

void MenuScene::setupBorders(const sf::Vector2f &size,
                             const sf::Vector2f &center) {
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

bool MenuScene::setupMenu(const sf::Vector2f &size,
                          const sf::Vector2f &center) {
    if (!_itemFont.loadFromFile("FiraMono-Regular.ttf")) {
        std::cerr << "ERROR: Couldn't load font \"FiraMono-Regular.ttf\"\n";
        return false;
    }

    _itemFont.setSmooth(true);
    sf::Vector2f corner(
            center.x - size.x / 2.f + margin * 2.f + width * 2.f,
            center.y - size.y / 2.f + margin * 2.f + width * 2.f
    );

    _menu.create(MENU_ITEM_COUNT, _itemFont, MENU_ITEM_FONT_SIZE);
    _menu.setIndent(MENU_ITEM_INDENT);

    _menu.fillItem(L"Выберите пункт меню из следующего списка:");
    _menu.fillItem(L"");
    _menu.fillItem(L"1) Заставка");
    _menu.fillItem(L"2) Графики уравнений");
    _menu.fillItem(L"3) Сведения об авторе");
    _menu.fillItem(L"");
    _menu.fillItem(PROMPT);

    _menu[SILLY].setString(L"(c) RETRO VIBES!!! awooo woof woof UwU");
    _menu[SILLY].setFillColor(sf::Color(70, 70, 70));

    sf::Vector2f menuSize = _menu.getSize();
    menuSize = _menu.setFixedSize(sf::Vector2f(
                size.x - margin * 2.f - width * 4.f,
                menuSize.y
    ));

    _menu.setOrigin(menuSize / 2.f);
    _menu.setPosition(center);

    return true;
}
