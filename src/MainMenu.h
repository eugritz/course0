#pragma once

#include <SFML/Graphics.hpp>

#include "MenuScene.h"

#define MAIN_MENU_INPUT_BLINKING_TIMEOUT 500000
#define MAIN_MENU_ITEM_COUNT 15
#define MAIN_MENU_ITEM_LENGTH 44

struct MenuItem {
    sf::String title;
    std::function<void()> callback;
    std::size_t itemIndex;
};

class MainMenu : public MenuScene {
    const sf::String PROMPT = "> ";

    sf::String _input;
    sf::Text *_inputText;
    bool _inputBlinking;
    bool _inputBlinkingSwitch;
    int _inputBlinkingTimeout;

    bool _inputControl;
    bool _inputAlt;

    std::vector<MenuItem> _items;
    std::size_t _inputFocusedItem;
    bool _inputFocusedFound;
    std::size_t _cursorFocusedItem;
    bool _cursorFocusedFound;

public:
    MainMenu(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setupMenu();

    void onTextEntered(const sf::Event::TextEvent &event);
    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
    void onMouseMoved(const sf::Event::MouseMoveEvent &event);
    void onMouseButtonPressed(const sf::Event::MouseButtonEvent &event);

    void inputHint();
    void addItem(MenuItem item);
};
