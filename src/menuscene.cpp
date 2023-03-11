#include "menuscene.h"

#include <cmath>
#include <iostream>

#include "fragrect.hpp"
#include "project0.h"
#include "resources.hpp"

const float margin = MENU_BORDER_MARGIN;
const float width = MENU_BORDER_WIDTH;

MenuScene::MenuScene(sf::RenderTarget *target) : Scene(target) {
    _colorOffsetTimeout = 0;
    _colorOffset = 0.f;
    _nextCharTimeout = 0.f;
    _inputBlinking = false;
    _inputBlinkingSwitch = false;
    _inputBlinkingTimeout = 0;
    _inputControl = false;
    _inputAlt = false;
    _inputFocusedItem = 0;
    _inputFocusedFound = false;

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
    if (_nextCharTimeout > MENU_CHAR_DRAWN_TIMEOUT) {
        _nextCharTimeout = 0;
        _menu.update();
    }

    if (_colorOffset > 2.f * M_PI)
        _colorOffset = 0.f;
    if (_colorOffsetTimeout > MENU_COLOR_OFFSET_TIMEOUT) {
        _colorOffsetTimeout = 0;
        _colorOffset += MENU_COLOR_OFFSET_STEP;
        _borderShader.setUniform("off", _colorOffset);
    }

    if (_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _inputText->getString();
        _inputText->setString(input + "_");
        _inputBlinkingSwitch = false;
    } else if (!_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _inputText->getString();
        _inputText->setString(input.substring(0, input.getSize() - 1));
        _inputBlinkingSwitch = false;
    }

    if (_inputBlinkingTimeout > MENU_INPUT_BLINKING_TIMEOUT) {
        _inputBlinkingTimeout = 0;
        _inputBlinking = !_inputBlinking;
        _inputBlinkingSwitch = true;
    }

    _colorOffsetTimeout += elapsed.asMicroseconds();
    _nextCharTimeout += elapsed.asMicroseconds();
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
        onTextEntered(event.text);
    } else if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    } else if (event.type == sf::Event::MouseMoved) {
        onMouseMoved(event.mouseMove);
    } else if (event.type == sf::Event::MouseButtonPressed) {
        onMouseButtonPressed(event.mouseButton);
    }
    return true;
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

    addItem({ L"1) Заставка", []() {
        Project0::getInstance()->postEvent(INTRO_OPEN);
    }});
    addItem({ L"2) Графики функций", []() {
        // TODO: graphs scene
    }});
    addItem({ L"3) Сведения об авторе", []() {
        // TODO: author info scene/dialog
    }});

    _menu.fillItem(L"");
    std::size_t inputIndex = _menu.fillItem(PROMPT);
    _inputText = &_menu[inputIndex];

    const std::size_t silly = MENU_ITEM_COUNT - 1;
    _menu[silly].setString(L"(c) RETRO VIBES!!! awooo woof woof UwU");
    _menu[silly].setFillColor(sf::Color(70, 70, 70));

    sf::Vector2f menuSize = _menu.getSize();
    menuSize = _menu.setFixedSize(sf::Vector2f(
        size.x - margin * 2.f - width * 4.f,
        menuSize.y
    ));
    _menu.setOrigin(menuSize / 2.f);
    _menu.setPosition(center);
    return true;
}

void MenuScene::onTextEntered(const sf::Event::TextEvent &event) {
    sf::String input = _inputText->getString();
    if (event.unicode == 8) {
        _input = _input.substring(0, _input.getSize() - 1);
    } else if (event.unicode > 31) {
        _input += event.unicode;
    } else {
        return;
    }

    _inputText->setString(PROMPT + _input);
    _inputBlinkingTimeout = 0;
    _inputBlinking = false;
    inputHint();
}

void MenuScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Enter) {
        if (_inputFocusedFound)
            _items[_inputFocusedItem].callback();
    }

    if (event.control)
        _inputControl = true;
    else if (event.alt)
        _inputAlt = true;
}

void MenuScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (event.control)
        _inputControl = false;
    else if (event.alt)
        _inputAlt = false;
}

void MenuScene::onMouseMoved(const sf::Event::MouseMoveEvent &event) {
    bool focused = false;
    for (auto it = _items.begin(); it != _items.end(); it++) {
        sf::Text *item = &_menu[it->itemIndex];
        sf::Vector2f cursor(event.x, event.y);
        sf::FloatRect bounds = item->getGlobalBounds();
        if (!focused && bounds.contains(cursor)) {
            item->setStyle(item->getStyle() | sf::Text::Bold);
            _cursorFocusedItem = it - _items.begin();
            focused = true;
        } else {
            item->setStyle(item->getStyle() & ~sf::Text::Bold);
        }
    }
    _cursorFocusedFound = focused;
}

void MenuScene::onMouseButtonPressed(const sf::Event::MouseButtonEvent &event) {
    if (event.button == sf::Mouse::Button::Left) {
        if (_cursorFocusedFound)
            _items[_cursorFocusedItem].callback();
    }
}

void MenuScene::inputHint() {
    std::size_t found = 0;
    for (auto it = _items.begin(); it != _items.end(); it++) {
        bool startsWith = true;
        std::size_t i = 0;
        while (i < _input.getSize() && i < it->title.getSize()) {
            if (_input[i] != it->title[i]) {
                startsWith = false;
                break;
            }
            i++;
        }

        sf::Text *item = &_menu[it->itemIndex];
        if (i > 0 && startsWith) {
            item->setStyle(item->getStyle() | sf::Text::Underlined);
            _inputFocusedFound = found == 0;
            if (_inputFocusedFound)
                _inputFocusedItem = it - _items.begin();
            found++;
        } else {
            item->setStyle(item->getStyle() & ~sf::Text::Underlined);
        }
    }

    if (found == 0) {
        _inputFocusedFound = false;
    }
}

void MenuScene::addItem(MenuItem item) {
    item.itemIndex = _menu.fillItem(item.title);
    _items.push_back(item);
}
