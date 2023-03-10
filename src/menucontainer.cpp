#include "menucontainer.h"

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
    _items.clear();
}

sf::Text &MenuContainer::operator[](std::size_t index) {
    return _items[index];
}

const sf::Text &MenuContainer::operator[](std::size_t index) const {
    return _items[index];
}

void MenuContainer::addItem(const sf::String &title) {
    sf::RectangleShape a;
    sf::Text item(title, _font, _characterSize);
    sf::Vector2f position(
            0, _items.size() * _characterSize + _items.size() * _indent
    );
    item.setPosition(_position + position);
    _items.push_back(item);
}

void MenuContainer::fillItem(const sf::String &title) {
    if (_current < _items.size()) {
        sf::Text item(title, _font, _characterSize);
        _items[_current].setString(title);
        _current++;
    }
}

std::size_t MenuContainer::getItemCount() const {
    return _items.size();
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

void MenuContainer::setPosition(const sf::Vector2f &position) {
    _position = position;
    for (int i = 0; i < _items.size(); i++) {
        sf::Vector2f position(0, i * _characterSize + i * _indent);
        _items[i].setPosition(_position - _origin + position);
    }
}

void MenuContainer::setOrigin(const sf::Vector2f &origin) {
    _origin = origin;
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

void MenuContainer::resetSize() {
    _isSizeFixed = false;
}

void MenuContainer::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    for (auto it : _items) {
        target.draw(it);
    }
}
