#include "MainMenu.h"

#include "Course0.h"
#include "Event/AuthorMenuOpenEvent.h"
#include "Event/ExitEvent.h"
#include "Event/IntroOpenEvent.h"
#include "Event/RacePlayerSelectionOpenEvent.h"
#include "Event/SynthesizerMenuOpenEvent.h"

MainMenu::MainMenu(sf::RenderTarget *target) : MenuScene(target) {
    _inputBlinking = false;
    _inputBlinkingSwitch = false;
    _inputBlinkingTimeout = 0;
    _inputControl = false;
    _inputAlt = false;
    _inputFocusedItem = 0;
    _inputFocusedFound = false;
    _inputArrows = false;
    _prevCursorFocusedItem = 0;
    _cursorFocusedItem = 0;

    const int width = MAIN_MENU_ITEM_LENGTH;
    const int height = MAIN_MENU_ITEM_COUNT;
    setup(width, height);
    setupMenu();
}

void MainMenu::setupMenu() {
    _menu.fillItem(L"Выберите пункт меню из следующего списка:");
    _menu.fillItem(L"");

    addItem({ L"1) Заставка", []() {
        Course0::getInstance()->postEvent(std::make_shared<IntroOpenEvent>());
    }});
    addItem({ L"2) Клавишный синтезатор", []() {
        Course0::getInstance()->postEvent(std::make_shared<SynthesizerMenuOpenEvent>());
    }});
    addItem({ L"3) Игра «Ипподром»", []() {
        Course0::getInstance()->postEvent(std::make_shared<RacePlayerSelectionOpenEvent>());
    }});
    addItem({ L"4) Сведения об авторе", []() {
        Course0::getInstance()->postEvent(std::make_shared<AuthorMenuOpenEvent>());
    }});
    addItem({ L"5) Выход", []() {
        Course0::getInstance()->postEvent(std::make_shared<ExitEvent>());
    }});

    _menu.fillItem(L"");
    std::size_t inputIndex = _menu.fillItem(PROMPT);
    _inputText = &_menu[inputIndex];

    const std::size_t silly = MAIN_MENU_ITEM_COUNT - 1;
    _menu[silly].setString(L"(c) RETRO VIBES!!! awooo woof woof UwU");
    _menu[silly].setFillColor(sf::Color(70, 70, 70));
}

void MainMenu::update(sf::Time elapsed) {
    MenuScene::update(elapsed);

    if (_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _inputText->getString();
        _inputText->setString(input + "_");
        _inputBlinkingSwitch = false;
    } else if (!_inputBlinking && _inputBlinkingSwitch) {
        sf::String input = _inputText->getString();
        _inputText->setString(input.substring(0, input.getSize() - 1));
        _inputBlinkingSwitch = false;
    }

    if (_inputBlinkingTimeout > MAIN_MENU_INPUT_BLINKING_TIMEOUT) {
        _inputBlinkingTimeout = 0;
        _inputBlinking = !_inputBlinking;
        _inputBlinkingSwitch = true;
    }

    _inputBlinkingTimeout += elapsed.asMicroseconds();
}

void MainMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool MainMenu::handleEvent(const sf::Event &event) {
    if (!MenuScene::handleEvent(event))
        return true;

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

void MainMenu::onTextEntered(const sf::Event::TextEvent &event) {
    sf::String input = _inputText->getString();

    _cursorFocusedFound = false;
    updateCursorFocus();

    if (event.unicode == 8) {
        _input = _input.substring(0, _input.getSize() - 1);
    } else if (event.unicode > 31 && event.unicode != 127) {
        _input += event.unicode;
    } else {
        return;
    }

    _inputText->setString(PROMPT + _input);
    _inputBlinkingTimeout = 0;
    _inputBlinking = false;
    inputHint();
}

void MainMenu::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Enter) {
        if (_inputFocusedFound)
            _items[_inputFocusedItem].callback();
        else if (_cursorFocusedFound && _inputArrows)
            _items[_cursorFocusedItem].callback();
    } else if (event.code == sf::Keyboard::Up) {
        if (!_inputArrows && !_inputFocusedFound) {
            _inputArrows = true;
            _prevCursorFocusedItem = _cursorFocusedItem = 0;
            _cursorFocusedFound = true;
        } else {
            moveCursorFocus(-1);
        }
        updateCursorFocus();
    } else if (event.code == sf::Keyboard::Down) {
        if (!_inputArrows && !_inputFocusedFound) {
            _inputArrows = true;
            _prevCursorFocusedItem = _cursorFocusedItem = 0;
            _cursorFocusedFound = true;
        } else {
            moveCursorFocus(+1);
        }
        updateCursorFocus();
    }

    if (event.control)
        _inputControl = true;
    else if (event.alt)
        _inputAlt = true;
}

void MainMenu::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (event.control)
        _inputControl = false;
    else if (event.alt)
        _inputAlt = false;
}

void MainMenu::onMouseMoved(const sf::Event::MouseMoveEvent &event) {
    if (_inputArrows)
        _inputArrows = false;
    for (auto it = _items.begin(); it != _items.end(); it++) {
        sf::Text *cur = &_menu[it->itemIndex];
        sf::Vector2f cursor(event.x, event.y);
        sf::FloatRect bounds = _menu.getTransform().transformRect(
            cur->getGlobalBounds()
        );

        if (bounds.contains(cursor)) {
            _cursorFocusedItem = it - _items.begin();
            _cursorFocusedFound = true;
            updateCursorFocus();
            return;
        }
    }
    _cursorFocusedFound = false;
}

void MainMenu::onMouseButtonPressed(const sf::Event::MouseButtonEvent &event) {
    if (event.button == sf::Mouse::Left) {
        if (_cursorFocusedFound && !_inputArrows)
            _items[_cursorFocusedItem].callback();
    }
}

void MainMenu::moveCursorFocus(int diff) {
    const std::size_t itemCount = _items.size();
    if (diff > 0) {
        if (_cursorFocusedItem == itemCount - 1) {
            _cursorFocusedItem = 0;
        } else {
            _cursorFocusedItem++;
        }
    } else if (diff < 0) {
        if (_cursorFocusedItem == 0)
            _cursorFocusedItem = itemCount - 1;
        else
            _cursorFocusedItem--;
    }
}

void MainMenu::updateCursorFocus() {
    sf::Text *cur = &_menu[_items[_cursorFocusedItem].itemIndex];
    sf::Text *prev = &_menu[_items[_prevCursorFocusedItem].itemIndex];

    if (!_cursorFocusedFound && _inputArrows) {
        _inputArrows = false;
        cur->setStyle(cur->getStyle() & ~sf::Text::Bold);
        return;
    }
    if (!_cursorFocusedFound)
        return;

    cur->setStyle(cur->getStyle() | sf::Text::Bold);
    if (_prevCursorFocusedItem != _cursorFocusedItem)
        prev->setStyle(prev->getStyle() & ~sf::Text::Bold);
    _prevCursorFocusedItem = _cursorFocusedItem;
}

void MainMenu::inputHint() {
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

void MainMenu::addItem(MenuItem item) {
    item.itemIndex = _menu.fillItem(item.title);
    _items.push_back(item);
}
