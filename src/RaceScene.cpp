#include "RaceScene.h"

#include <algorithm>
#include <cmath>

#include "Course0.h"

const int LEVEL[] = {
    264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264,
    264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264,
    264, 264, 154, 155, 155, 155, 155, 155, 155, 155, 155, 155, 156, 264, 264,
    264, 154, 204, 177, 177, 177, 177, 177, 177, 177, 177, 177, 203, 156, 264,
    154, 204, 177, 181, 199, 199, 199, 199, 199, 199, 199, 182, 177, 203, 156,
    176, 177, 181, 200, 264, 264, 264, 264, 264, 264, 264, 198, 182, 177, 178,
    176, 177, 178, 264, 264, 264, 264, 264, 264, 264, 264, 264, 176, 177, 178,
    176, 177, 203, 156, 264, 264, 264, 264, 264, 264, 264, 154, 204, 177, 178,
    198, 182, 177, 203, 155, 155, 155, 155, 155, 155, 155, 204, 177, 181, 200,
    264, 198, 182, 177, 177, 177, 177, 177, 177, 177, 177, 177, 181, 200, 264,
    264, 264, 198, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 264, 264,
    264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264,
    264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264, 264,
};

RaceScene::RaceScene(sf::RenderTarget *target) : Scene(target) {
    sf::Vector2u size = _target->getSize();
    _size = sf::Vector2f((float)size.x, (float)size.y);
    _finishing = false;
    _raceDelay = 0;
    setup();
}

void RaceScene::setup() {
    _map.load("./Tiles/TilesetFloor.png", sf::Vector2u(16, 16), LEVEL, 15, 13);
    _map.scale(2.5f, 2.5f);
    _map.setOrigin(_map.getSize() / 2.f);
    _map.setPosition(_size / 2.f);

    setupTrack(_tracks[0], sf::Vector2f(RACE_TRACK_SIZE_X, RACE_TRACK_SIZE_Y));
    setupTrack(_tracks[1], sf::Vector2f(RACE_TRACK_SIZE_X - 40.f, RACE_TRACK_SIZE_Y - 40.f));
    setupTrack(_tracks[2], sf::Vector2f(RACE_TRACK_SIZE_X - 80.f, RACE_TRACK_SIZE_Y - 80.f));
    setupPlayer(_participants[0], _circles[0]);
    setupPlayer(_participants[1], _circles[1]);
    setupPlayer(_participants[2], _circles[2]);
}

void RaceScene::setupTrack(RectangleShape2 &track, const sf::Vector2f &size) {
    track.setSize(size);
    track.setOrigin(track.getSize() / 2.f);
    track.setPosition(_size / 2.f);

    track.setRoundness(RACE_TRACK_ROUNDNESS);
    track.setIterationCount(RACE_TRACK_ITERATIONS, true);
    track.setFillColor(sf::Color::Transparent);
    track.setOutlineColor(sf::Color::White);
    track.setOutlineThickness(5.f);
}

void RaceScene::setupPlayer(Player &participant, sf::CircleShape &circle) {
    circle.setRadius(10.f);
    circle.setOrigin(circle.getLocalBounds().getSize() / 2.f);
    circle.setFillColor(sf::Color::Red);
}

bool RaceScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    }
    return true;
}

void RaceScene::update(sf::Time elapsed) {
    if (_raceDelay < RACE_DELAY) {
        _raceDelay += elapsed.asMicroseconds();
        return;
    } else {
        _raceDelay -= RACE_DELAY;
    }

    for (size_t i = 0; i < RACE_PARTICIPANTS; i++) {
        const RectangleShape2 &track = _tracks[i];
        Player &participant = _participants[i];
        participant.tick += participant.speed;

        while (participant.tick > 1.f) {
            participant.bound++;
            if (participant.bound > track.getPointCount()) {
                participant.bound = 0;
            }

            participant.tick -= 1.f;
        }

        _circles[i].setPosition(_tracks[i].getPoint(_participants[i].bound));
    }
}

void RaceScene::draw(sf::RenderStates states) {
    _target->draw(_map);

    for (size_t i = 0; i < RACE_PARTICIPANTS; i++) {
        const RectangleShape2 &track = _tracks[i];
        _target->draw(track);
        _target->draw(_circles[i], track.getTransform());
    }
}

void RaceScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Escape) {
        _finishing = true;
    }
}

void RaceScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        Course0::getInstance()->postEvent(MENU_OPEN);
        _finishing = false;
    }
}
