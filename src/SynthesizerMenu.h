#pragma once

#include <SFML/Graphics.hpp>

#include "MenuScene.h"
#include "Synthesizer.h"

#define SYNTHESIZER_MENU_ITEM_COUNT 15
#define SYNTHESIZER_MENU_ITEM_LENGTH 44

class SynthesizerMenu : public MenuScene {
    const sf::String KEY_NOTES = "q2w3er5t6y7ui";

    ScopedPaHandler _handler;
    Synthesizer _synth;
    sf::String _pressedNotes;

    bool _finishing;

public:
    SynthesizerMenu(sf::RenderTarget *target);

    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setupMenu();

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);

    void addKeySemitone(char key);
    void removeKeySemitone(char key);
};
