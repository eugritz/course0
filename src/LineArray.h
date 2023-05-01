#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Line.h"

class LineArray : public sf::Drawable {
  std::vector<sf::VertexArray> _arr;
  Line _last;

public:
    enum JoinPriority {
        LINE_PRIORITY,
        SEGMENT_PRIORITY,
    };

    LineArray();

    std::size_t getVertexCount() const;

    int join(const Line &segment, JoinPriority priority);
    void clear();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
