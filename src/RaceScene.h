#pragma once

#include <SFML/Graphics.hpp>

#include "RectangleShape2.h"
#include "Scene.h"
#include "TileMap.hpp"

#define RACE_TRACK_SIZE_X 510.f
#define RACE_TRACK_SIZE_Y 270.f
#define RACE_TRACK_ROUNDNESS 0.5f
#define RACE_TRACK_ITERATIONS 50
#define RACE_PARTICIPANTS 3
#define RACE_DELAY 0

struct Player {
    size_t bound;
    float tick;
    float speed;

    Player() : bound(0), tick(0), speed(1.0f) {}
};

class RaceScene : public Scene {
    sf::Vector2f _size;
    bool _finishing;

    TileMap _map;
    RectangleShape2 _tracks[RACE_PARTICIPANTS];
    Player _participants[RACE_PARTICIPANTS];
    sf::CircleShape _circles[RACE_PARTICIPANTS];

    int _raceDelay;

public:
    RaceScene(sf::RenderTarget *target);

    void update(sf::Time elapsed);
    void draw(sf::RenderStates states);
    bool handleEvent(const sf::Event &event);

private:
    void setup();
    void setupTrack(RectangleShape2 &track, const sf::Vector2f &size);
    void setupPlayer(Player &participant, sf::CircleShape &circle);

    void onKeyPressed(const sf::Event::KeyEvent &event);
    void onKeyReleased(const sf::Event::KeyEvent &event);
};
