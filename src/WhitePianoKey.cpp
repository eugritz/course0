#include "WhitePianoKey.h"

#include <random>

WhitePianoKey::WhitePianoKey(const sf::Font &font, const sf::String &note) {
    _isPressed = false;
    _note = note;
    _font = font;
}

void WhitePianoKey::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    const float width = getSize().x;
    const float height = getSize().y;
    const float centerOffsetX = -2.f;

    sf::Text label(_note, _font, 32);
    label.setOrigin(label.getLocalBounds().getSize() / 2.f);
    label.setPosition(width / 2.f + centerOffsetX, height - 32.f);
    label.setFillColor(sf::Color::Black);

    sf::VertexArray vertices(sf::Quads);

    if (!_isPressed) {
        vertices.append(sf::Vertex({ 0.0f, 0.0f }, sf::Color(255, 255, 255)));
        vertices.append(sf::Vertex({ width, 0.0f }, sf::Color(255, 255, 255)));
        vertices.append(sf::Vertex({ width, height }, sf::Color(120, 120, 120)));
        vertices.append(sf::Vertex({ 0.0f, height }, sf::Color(140, 140, 140)));
    } else {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dist(-1.5, 1.5);

        label.setPosition(label.getPosition().x + dist(gen),
                          label.getPosition().y + dist(gen));

        vertices.append(sf::Vertex({ 0.0f, 0.0f }, sf::Color(230, 230, 230)));
        vertices.append(sf::Vertex({ width, 0.0f }, sf::Color(230, 230, 230)));
        vertices.append(sf::Vertex({ width, height }, sf::Color(90, 90, 90)));
        vertices.append(sf::Vertex({ 0.0f, height }, sf::Color(80, 80, 80)));
    }

    target.draw(vertices, states);
    target.draw(label, states);
}

sf::Vector2f WhitePianoKey::getSize() const {
    const float width = 50.f;
    const float height = 150.f;
    return { width, height };
}
