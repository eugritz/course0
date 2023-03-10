#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <vector>

#include "fragrect.hpp"
#include "menucontainer.h"
#include "scene.h"

#define MENU_BORDER_MARGIN 10.f
#define MENU_BORDER_WIDTH 5.f
#define MENU_CHAR_DRAWN_TIMEOUT 7000
#define MENU_COLOR_OFFSET_STEP 0.001f
#define MENU_COLOR_OFFSET_TIMEOUT 1000
#define MENU_INPUT_BLINKING_TIMEOUT 500000
#define MENU_ITEM_COUNT 15
#define MENU_ITEM_FONT_SIZE 14
#define MENU_ITEM_INDENT 2.f

struct MenuItem {
    sf::String title;
    std::function<void()> callback;
    std::size_t itemIndex;
};

class MenuScene : public Scene {
    const sf::String PROMPT = "> ";

    sf::RectangleShape _background;
    FragmentRectangleShape _r1, _r2, _r3, _r4;
    sf::Shader _borderShader;
    int _colorOffsetTimeout;
    float _colorOffset;

    MenuContainer _menu;
    sf::Font _itemFont;
    int _nextCharTimeout;

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
    MenuScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setupBorders(const sf::Vector2f &size, const sf::Vector2f &center);
    bool setupMenu(const sf::Vector2f &size, const sf::Vector2f &center);

    void onTextEntered(const sf::Event::TextEvent &event);
    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
    void onMouseMoved(const sf::Event::MouseMoveEvent &event);
    void onMouseButtonPressed(const sf::Event::MouseButtonEvent &event);

    void inputHint();
    void addItem(MenuItem item);
};
