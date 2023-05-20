#include "RaceScene.h"

#include <algorithm>
#include <cmath>
#include <random>

#include "Course0.h"
#include "Event/MenuOpenEvent.h"

// Backgrounds/Tilesets/TilesetFloor.png
const int LAYER0[] = {
    264, 264, 264, 245, 264, 264, 245, 264, 264, 244, 264, 264, 264, 264, 287,
    244, 264, 264, 264, 264, 264, 264, 264, 244, 264, 264, 266, 264, 264, 264,
    264, 245, 154, 155, 155, 155, 155, 155, 155, 155, 155, 155, 156, 264, 264,
    264, 154, 204, 177, 177, 177, 177, 177, 242, 177, 177, 243, 203, 156, 264,
    154, 204, 177, 181, 199, 199, 199, 199, 199, 199, 199, 182, 177, 203, 156,
    176, 177, 181, 200, 244, 264, 264, 264, 264, 245, 264, 198, 182, 177, 178,
    176, 242, 178, 245, 264, 266, 264, 264, 264, 264, 244, 264, 176, 177, 178,
    176, 177, 203, 156, 264, 245, 264, 244, 245, 264, 264, 154, 204, 177, 178,
    198, 182, 177, 203, 155, 155, 155, 155, 155, 155, 155, 204, 177, 181, 200,
    264, 198, 182, 177, 177, 177, 243, 177, 177, 177, 177, 177, 181, 200, 245,
    264, 264, 198, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 264, 265,
    245, 245, 264, 264, 264, 244, 264, 264, 264, 264, 264, 264, 264, 264, 264,
    136, 244, 264, 264, 264, 264, 264, 264, 244, 245, 266, 264, 264, 245, 264,
};

// Backgrounds/Tilesets/TilesetFloorDetail.png
const int LAYER1[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1,
    -1, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, 37, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  1, -1, -1, -1,
    -1, 38, -1, -1, -1, -1, -1, 36, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33,
};

// Backgrounds/Tilesets/TilesetElement.png
const int LAYER2[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1,  2,  2,  2,  2,  2,  2,  2, -1, -1, 48, 49,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, 65,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 75, 33, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,107, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

RaceScene::RaceScene(sf::RenderTarget *target,
                     PlayerOption players[RACE_PLAYERS], size_t selected)
        : Scene(target) {
    sf::Vector2u size = _target->getSize();
    _size = sf::Vector2f((float)size.x, (float)size.y);
    _finishing = false;
    _selected = selected;
    _hasWinner = false;
    _colorSwitchDelay = 0;
    _raceDelay = 0;

    setupOptions(players);
    setup();
}

void RaceScene::setup() {
    setupTileMap(_layers[0], "./Resources/Backgrounds/Tilesets/TilesetFloor.png", LAYER0);
    setupTileMap(_layers[1], "./Resources/Backgrounds/Tilesets/TilesetFloorDetail.png", LAYER1);
    setupTileMap(_layers[2], "./Resources/Backgrounds/Tilesets/TilesetElement.png", LAYER2);

    const sf::Vector2f trackSize(RACE_TRACK_SIZE_X, RACE_TRACK_SIZE_Y);
    const sf::Vector2f indent(RACE_TRACK_INDENT, RACE_TRACK_INDENT);
    setupTrack(_tracks[0], trackSize);
    setupTrack(_tracks[1], trackSize - indent);
    setupTrack(_tracks[2], trackSize - 2.f * indent);
    syncTrackVertices(_tracks[0], _tracks[2]);
    syncTrackVertices(_tracks[1], _tracks[2]);

    _tracks[0].setOutlineColor(sf::Color(0, 0, 0, 10));
    _tracks[1].setOutlineColor(sf::Color(0, 0, 0, 0));
    _tracks[2].setOutlineColor(sf::Color(0, 0, 0, 10));

    setupPlayer(_players[0], _tracks[0]);
    setupPlayer(_players[1], _tracks[1]);
    setupPlayer(_players[2], _tracks[2]);

    _timer.create(sf::seconds(RACE_TIMER_DURATION));
    _timer.setOrigin(_timer.getSize() / 2.f);
    _timer.setPosition(_size / 2.f);

    auto finishFont = GlobalResourceManager::ref<sf::Font>("TIMER_FONT");
    _finishNameLabel.setFont(**finishFont);
    _finishNameLabel.setString("Finish!");
    _finishNameLabel.setCharacterSize(64);

    _finishNameLabel.setFillColor(sf::Color::Red);
    _finishNameLabel.setOutlineThickness(5.f);
    _finishNameLabel.setOutlineColor(sf::Color::Black);
    _finishLabel = _finishNameLabel;
}

void RaceScene::setupOptions(PlayerOption options[RACE_PLAYERS]) {
    _nameFont = GlobalResourceManager::ref<sf::Font>("SCROLL_FONT");

    for (size_t i = 0; i < RACE_PLAYERS; i++) {
        _players[i].type = options[i].type;
        _players[i].nameLabel.setFont(**_nameFont);
        _players[i].nameLabel.setString(options[i].name);
        _players[i].nameLabel.setCharacterSize(10);
        _players[i].nameLabel.setOrigin(
                _players[i].nameLabel.getLocalBounds().getSize() / 2.f);
        _players[i].nameLabel.setOutlineThickness(1.f);
        _players[i].nameLabel.setOutlineColor(sf::Color::Black);
        if (i == _selected)
            _players[i].nameLabel.setFillColor(sf::Color::Yellow);
    }
}

void RaceScene::setupTileMap(TileMap &tileMap, const std::string &tileset,
                             const int *layer) {
    tileMap.load(tileset, sf::Vector2u(16, 16), layer, 15, 13);
    tileMap.scale(RACE_PIXEL_SCALE, RACE_PIXEL_SCALE);
    tileMap.setOrigin(tileMap.getSize() / 2.f);
    tileMap.setPosition(_size / 2.f);
}

void RaceScene::setupTrack(RectangleShape2 &track, const sf::Vector2f &size) {
    track.setSize(size);
    track.setOrigin(track.getSize() / 2.f);
    track.setPosition(_size / 2.f);

    track.setRoundness(RACE_TRACK_ROUNDNESS);
    track.setIterationCount(RACE_TRACK_ITERATIONS, true);
    track.setFillColor(sf::Color::Transparent);
    track.setOutlineColor(sf::Color::White);
    track.setOutlineThickness(20.f);
}

void RaceScene::syncTrackVertices(RectangleShape2 &dest,
                                  const RectangleShape2 &source) {
    dest.setIterationCount(source.getIterationCount() *
            dest.getCurveLength() / source.getCurveLength(), true);
}

void RaceScene::setupPlayer(Player &player, RectangleShape2 &track) {
    player.racer.create(player.type);
    player.racer.setScale(RACE_PIXEL_SCALE, RACE_PIXEL_SCALE);

    std::size_t iters = track.getIterationCount();
    sf::Vector2u itersXY = track.getAxesIterationCount();
    player.bound = itersXY.x + itersXY.y + 2 * iters - RACE_PLAYER_OFFSET_START;
    player.start = itersXY.x + itersXY.y + 2 * iters - RACE_PLAYER_OFFSET_START;

    player.racer.setDirection(RIGHT);
    updatePlayerPosition(player, track);
}

bool RaceScene::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        onKeyPressed(event.key);
    } else if (event.type == sf::Event::KeyReleased) {
        onKeyReleased(event.key);
    }
    return true;
}

void RaceScene::onKeyPressed(const sf::Event::KeyEvent &event) {
    if (event.code == sf::Keyboard::Escape) {
        _finishing = true;
    }
}

void RaceScene::onKeyReleased(const sf::Event::KeyEvent &event) {
    if (_finishing) {
        Course0::getInstance()->postEvent(std::make_shared<MenuOpenEvent>());
        _finishing = false;
    }
}

void RaceScene::update(sf::Time elapsed) {
    if (!_timer.isFinished()) {
        _timer.update(elapsed);
        _timer.setOrigin(_timer.getSize() / 2.f);
        _timer.setPosition(_size / 2.f);
        return;
    }

    if (_raceDelay < RACE_DELAY) {
        _raceDelay += elapsed.asMicroseconds();
        return;
    } else {
        _raceDelay -= RACE_DELAY;
    }

    if (!_hasWinner && _finishers.size() > 0) {
        onFinishPassed();
        _hasWinner = true;
    }
    if (_hasWinner) {
        if (_colorSwitchDelay >= RACE_COLOR_SWITCH_DELAY) {
            sf::Color tmp = _finishNameLabel.getFillColor();
            _finishNameLabel.setFillColor(_finishLabel.getFillColor());
            _finishLabel.setFillColor(tmp);
            _colorSwitchDelay -= RACE_COLOR_SWITCH_DELAY;
        }
        _colorSwitchDelay += elapsed.asMicroseconds();
    }

    for (size_t i = 0; i < RACE_PLAYERS; i++) {
        const RectangleShape2 &track = _tracks[i];
        Player &player = _players[i];
        player.tick += player.racer.getSpeed();

        while (player.tick > 1.f) {
            size_t previous = player.bound--;
            if (player.bound > track.getPointCount()) {
                player.bound = track.getPointCount() - 1;
            }

            sf::Vector2f p0 = track.getPoint(previous);
            sf::Vector2f p1 = track.getPoint(player.bound);
            float cat = std::sqrt(std::pow(p1.x - p0.x, 2) +
                                  std::pow(p1.y - p0.y, 2));
            float hyp = p1.y - p0.y;
            float angle = std::asin(hyp / cat);

            if (angle > M_PI / 4.f) {
                player.racer.setDirection(DOWN);
            } else if (angle < -M_PI / 4.f) {
                player.racer.setDirection(UP);
            } else if (p1.x - p0.x > 0) {
                player.racer.setDirection(RIGHT);
            } else if (p1.x - p0.x < 0) {
                player.racer.setDirection(LEFT);
            }

            float offX = track.getGlobalBounds().left;
            float offY = track.getGlobalBounds().top;
            float halfX = _size.x / 2.f;
            float halfY = _size.y / 2.f;
            bool passedHalfX = offX + p0.x <= halfX && halfX <= offX + p1.x ||
                               offX + p1.x <= halfX && halfX <= offX + p0.x;
            bool passedHalfY = offY + p0.y <= halfY && halfY <= offY + p1.y ||
                               offY + p1.y <= halfY && halfY <= offY + p0.y;
            bool passedQuarter = passedHalfX || passedHalfY;
            if (passedQuarter) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution dist(0.6, 1.0);
                player.racer.setSpeed(dist(gen));
            }

            bool finished = player.bound == player.start;
            if (finished && _finishers.size() < 4)
                _finishers.push_back(i);

            player.tick -= 1.f;
        }

        player.racer.update(elapsed);
        updatePlayerPosition(player, track);
    }
}

void RaceScene::draw(sf::RenderStates states) {
    for (size_t i = 0; i < sizeof(_layers) / sizeof(TileMap); i++) {
        _target->draw(_layers[i]);
    }

    std::vector<size_t> indexes;
    for (size_t i = 0; i < RACE_PLAYERS; i++)
        indexes.push_back(i);
    while (!indexes.empty()) {
        std::vector<size_t>::iterator min = indexes.begin();
        for (auto it = indexes.begin(); it != indexes.end(); it++) {
            if (_players[*it].racer.getPosition().y <
                _players[*min].racer.getPosition().y)
                min = it;
        }

        const RectangleShape2 &track = _tracks[*min];
        _target->draw(track);
        _target->draw(_players[*min].racer, track.getTransform());
        _target->draw(_players[*min].nameLabel, track.getTransform());
        indexes.erase(min);
    }

    if (!_timer.isFinished())
        _target->draw(_timer);
    if (_hasWinner) {
        _target->draw(_finishNameLabel);
        _target->draw(_finishLabel);
    }
}

void RaceScene::onFinishPassed() {
    _finishNameLabel.setString(_players[_finishers[0]].nameLabel.getString());
    _finishNameLabel.setOrigin(_finishNameLabel.getLocalBounds().getSize() / 2.f);
    _finishNameLabel.setPosition(_size / 2.f);
    _finishNameLabel.setFillColor(sf::Color::Red);

    if (_finishers[0] == _selected) {
        _finishLabel.setString(")you won)");
    } else {
        _finishLabel.setString("has won");
    }
    _finishLabel.setOrigin(_finishLabel.getLocalBounds().getSize() / 2.f);
    float nameLabelHeight = _finishNameLabel.getLocalBounds().getSize().y;
    _finishLabel.setPosition(_size / 2.f + sf::Vector2f(0, nameLabelHeight));
    _finishNameLabel.setFillColor(sf::Color::White);
}

void RaceScene::updatePlayerPosition(Player &player, const RectangleShape2 &track) {
    sf::Vector2f playerPosition(track.getPoint(player.bound) +
            sf::Vector2f(0, RACE_PLAYER_OFFSET_Y));
    player.racer.setPosition(playerPosition);
    playerPosition.y -= player.racer.getSize().y;
    player.nameLabel.setPosition(playerPosition);
}
