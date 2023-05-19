#pragma once

#include <SFML/Graphics.hpp>

#include <random>

#include "Event/RaceOpenEvent.h"
#include "Scene.h"
#include "Scroll.hpp"

const sf::String NAMES[] = { "John",    "Doe",      "Jack",    "Sparrow",
                             "James",   "Bond",     "Tony",    "Stark",
                             "Peter",   "Parker",   "Jabba",   "the Hutt",
                             "Lara",    "Croft",    "Scrudge", "McDuck",  
                             "Rock",    "Lee",      "Sandy",   "Cheeks",
                             "Leonard", "McCoy",    "Gregory", "House",
                             "Dorian",  "Gray",     "Ellen",   "Ripley",
                             "Calvin",  "McMurray", "Uni",     "Cornelius" };

class RacePlayerSelectionScene : public Scene {
    sf::Vector2f _size;
    bool _finishing;
    std::mt19937 _gen;

    Scroll _scrolls[3];
    PlayerOption _players[3];
    size_t _prevSelectedPlayer, _selectedPlayer;

public:
    RacePlayerSelectionScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);

    sf::String generateName();
    void moveSelection(int diff);
};
