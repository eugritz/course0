#include "menucontainer.h"
#include <iostream>

MenuContainer::MenuContainer() { }
MenuContainer::MenuContainer(const sf::Font &font, unsigned characterSize) {
    create(font, characterSize);
}

MenuContainer::MenuContainer(std::size_t size, const sf::Font &font,
                             unsigned characterSize) {
    create(size, font, characterSize);
}

void MenuContainer::create(const sf::Font &font, unsigned characterSize) {
    _font = font;
    _characterSize = characterSize;
    reset();
}

void MenuContainer::create(std::size_t size, const sf::Font &font,
                  unsigned characterSize) {
    _font = font;
    _characterSize = characterSize;
    reset();

    for (int i = 0; i < size; i++) {
        addItem("");
    }
}

void MenuContainer::reset() {
    _current = 0;
    _indent = 0.f;
    _isSizeFixed = false;
    _charactersShown = 0;
    _finishAnimation = false;
    _items.clear();
}

sf::Text &MenuContainer::operator[](std::size_t index) {
    return _items[index];
}

const sf::Text &MenuContainer::operator[](std::size_t index) const {
    return _items[index];
}

std::size_t MenuContainer::addItem(const sf::String &title) {
    sf::Text item(title, _font, _characterSize);
    sf::Vector2f position(
            0, _items.size() * _characterSize + _items.size() * _indent
    );
    item.setPosition(_position + position);
    _items.push_back(item);
    return _items.size() - 1;
}

std::size_t MenuContainer::fillItem(const sf::String &title) {
    if (_current < _items.size()) {
        _items[_current].setString(title);
        _current++;
        return _current - 1;
    }
    return -1;
}

std::size_t MenuContainer::fillFromStream(std::wstringstream &stream) {
    std::wstring line;
    bool inBounds = _current < _items.size();
    while (inBounds && std::getline(stream, line)) {
        fillItem(line);
        inBounds = _current < _items.size();
    }
    return inBounds;
}

std::size_t MenuContainer::getItemCount() const {
    return _items.size();
}

std::size_t MenuContainer::getTotalLength() const {
    std::size_t charCount = 0;
    for (auto it = _items.begin(); it != _items.end(); it++) {
        charCount += it->getString().getSize();
    }
    return charCount;
}

void MenuContainer::setIndent(float indent) {
    _indent = indent;
    for (int i = 0; i < _items.size(); i++) {
        sf::Vector2f position(0, i * _characterSize + i * _indent);
        _items[i].setPosition(_position + position);
    }
}

const sf::Vector2f &MenuContainer::setFixedSize(const sf::Vector2f &size) {
    _isSizeFixed = true;
    _size = size;
    return size;
}

sf::Vector2f MenuContainer::getSize() const {
    if (_isSizeFixed)
        return _size;
    sf::Vector2f size;
    for (auto it : _items) {
        if (it.getLocalBounds().width > size.x)
            size.x = it.getLocalBounds().width;
    }
    size.y = _items.size() * _characterSize + _items.size() * _indent;
    return size;
}

void MenuContainer::resetSize() {
    _isSizeFixed = false;
}

void MenuContainer::setAnimationFinished(bool state) {
    _finishAnimation = state;
}

void MenuContainer::update() {
    _charactersShown++;
}

void MenuContainer::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    // TODO: optimize
    std::size_t shown = 0;
    states.transform *= getTransform();
    for (auto it = _items.begin(); it != _items.end(); it++) {
        sf::Text shadow(*it);
        sf::String s = shadow.getString();
        if (_finishAnimation) {
            target.draw(shadow, states);
        } else if (_charactersShown - shown > 0) {
            sf::String tmp = s.substring(0, _charactersShown - shown);
            if (_charactersShown - shown <= s.getSize())
                tmp += CARRIAGE;
            shadow.setString(tmp);
            target.draw(shadow, states);
        }

        if (_charactersShown - shown > s.getSize()) {
            shown += s.getSize();
        } else if (!_finishAnimation) {
            break;
        }
    }
}
