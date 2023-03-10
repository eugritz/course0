#pragma once

#include <SFML/Graphics.hpp>

#include "fragrect.hpp"
#include "scene.h"

#define MENU_BORDER_MARGIN 10.f
#define MENU_BORDER_WIDTH 5.f
#define MENU_COLOR_OFFSET_TIMEOUT 50
#define MENU_INPUT_BLINKING_TIMEOUT 500000

class MenuScene : public Scene {
    const sf::String PROMPT = "> ";

    sf::RectangleShape _background;

    FragmentRectangleShape _r1, _r2, _r3, _r4;
    sf::Shader _borderShader;
    int _colorOffsetTimeout;
    float _colorOffset;

    sf::Font _itemFont;
    sf::Text _menu[5];

    sf::String _input;
    bool _inputBlinking;
    bool _inputBlinkingSwitch;
    int _inputBlinkingTimeout;

    bool _inputControl;
    bool _inputAlt;

    enum MenuTextOptions {
        INTRO = 0,
        GRAPH,
        AUTHOR,
        INPUT,
        SILLY,
    };

public:
    MenuScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setupBorders(const sf::Vector2f &size, const sf::Vector2f &center);
    void setupText(const sf::Vector2f &size, const sf::Vector2f &center);
};
