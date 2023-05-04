#include "BlackPianoKey.h"

#include <random>

BlackPianoKey::BlackPianoKey(const sf::Font &font, const sf::String &note) {
    _isPressed = false;
    _note = note;
    _font = font;
}

void BlackPianoKey::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    const float width = getSize().x;
    const float height = getSize().y;
    const float centerOffsetX = -2.f;

    sf::Text label(_note, _font, 24);
    label.setOrigin(label.getLocalBounds().getSize() / 2.f);
    label.setPosition(width / 2.f + centerOffsetX, height - 24);
    label.setFillColor(sf::Color::White);

    sf::VertexArray vertices(sf::Quads);

    if (!_isPressed) {
        vertices.append(sf::Vertex({ 0.0f, 0.0f }, sf::Color(30, 30, 30)));
        vertices.append(sf::Vertex({ width, 0.0f }, sf::Color(30, 30, 30)));
        vertices.append(sf::Vertex({ width, height }, sf::Color(0, 0, 0)));
        vertices.append(sf::Vertex({ 0.0f, height }, sf::Color(0, 0, 0)));

    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dist(-1.5, 1.5);

        label.setPosition(label.getPosition().x + dist(gen),
                          label.getPosition().y + dist(gen));

        vertices.append(sf::Vertex({ 0.0f, 0.0f }, sf::Color(90, 90, 90)));
        vertices.append(sf::Vertex({ width, 0.0f }, sf::Color(90, 90, 90)));
        vertices.append(sf::Vertex({ width, height }, sf::Color(40, 40, 40)));
        vertices.append(sf::Vertex({ 0.0f, height }, sf::Color(40, 40, 40)));
    }

    target.draw(vertices, states);
    target.draw(label, states);
}

sf::Vector2f BlackPianoKey::getSize() const {
    const float width = 40.f;
    const float height = 80.f;
    return { width, height };
}
