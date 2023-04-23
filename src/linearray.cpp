#include "linearray.h"
#include <iostream>

LineArray::LineArray() { }

void LineArray::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto it = _arr.begin(); it != _arr.end(); it++) {
        target.draw(*it, states);
    }
}

int LineArray::join(const Line &segment, JoinPriority priority) {
    sf::VertexArray arr = segment.toArray();
    if (arr.getVertexCount() != 4 ||
        arr.getPrimitiveType() != sf::TriangleStrip) {
        return 0;
    }

    if (_last.getEnd() != segment.getStart()) {
        _arr.push_back(sf::VertexArray(sf::TriangleStrip));
    }

    sf::VertexArray &back = _arr.back();
    _last = segment;

    if (back.getVertexCount() == 0) {
        back.append(arr[0]);
        back.append(arr[1]);
        back.append(arr[2]);
        back.append(arr[3]);
        return 1;
    }

    if (priority == LINE_PRIORITY) {
        back.append(arr[2]);
        back.append(arr[3]);
    } else if (priority == SEGMENT_PRIORITY) {
        back[back.getVertexCount() - 2] = arr[0];
        back[back.getVertexCount() - 1] = arr[1];
        back.append(arr[2]);
        back.append(arr[3]);
    }

    return 1;
}

void LineArray::clear() {
    _arr.clear();
}

std::size_t LineArray::getVertexCount() const {
    std::size_t count = 0;
    for (auto it = _arr.begin(); it != _arr.end(); it++) {
        count += it->getVertexCount();
    }
    return count;
}
