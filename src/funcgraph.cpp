#include "funcgraph.h"

FuncGraph::FuncGraph() {
    init();
}

FuncGraph::FuncGraph(const sf::Vector2u &size) {
    init();
    create(size);
}

void FuncGraph::init() {
    _scale = GRAPH_SCALE_START;
    _needsRefresh = true;
}

void FuncGraph::create(const sf::Vector2u &size) {
    _size.x = size.x;
    _size.y = size.y;
    _absCenter.x = size.x / 2.f;
    _absCenter.y = size.y / 2.f;
    _absOrigin = _absCenter;
    _visibleArea = sf::FloatRect(0.f, 0.f, _size.x, _size.y);
}

void FuncGraph::add(const Function &func) {
    _funcs.push_back({ func, LineArray() });
}

void FuncGraph::update() {
    if (!_needsRefresh)
        return;

    for (auto it = _funcs.begin(); it != _funcs.end(); it++) {
        it->lines.clear();
        calculate(*it);
    }

    _needsRefresh = false;
}

void FuncGraph::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto it = _funcs.begin(); it != _funcs.end(); it++) {
        target.draw(it->lines, states);
    }
}

void FuncGraph::calculate(CachedFunction &cached) {
    const float step = _scale / 1000.f;
    const float tinyStep = step / 10.f;

    const float start = relativeCoords(0, 0).x - _scale / 10.f;
    const float end = relativeCoords(_size.x, 0).x + _scale / 10.f;

    FuncDirection direction = CONTINUOUS;
    sf::Vector2f position = absoluteCoords(start, cached.func.func(start));

    bool jump = false;
    std::size_t dirLasted = 0;
    FuncDirection funcDirection = CONTINUOUS;

    auto jumped = [&](const sf::Vector2f &pos, FuncDirection dir) {
        bool switched = funcDirection != CONTINUOUS && dir != funcDirection;
        bool spike = std::abs(pos.y - position.y) > GRAPH_SPIKE_DIFF;
        return switched && spike;
    };

    for (float x = start + step; x < end; x += step) {
        float y = cached.func.func(x);
        sf::Vector2f nextPosition = absoluteCoords(x, y);
        FuncDirection nextDirection;
        nextDirection = position.y < nextPosition.y ? DESCENDING : ASCENDING;

        jump = jumped(nextPosition, nextDirection);
        if (direction == nextDirection)
            dirLasted++;
        if (!jump && dirLasted > _scale)
            funcDirection = nextDirection;

        Line segment(GRAPH_WIDTH);

        if (jump) {
            sf::Vector2f pos;
            float precisionStep = tinyStep;
            float lastX = x - step;
            do {
                float localX = lastX + precisionStep;
                float localY = cached.func.func(localX);
                pos = absoluteCoords(localX, localY);
                FuncDirection dir = position.y < pos.y ? DESCENDING : ASCENDING;
                if (jumped(pos, dir)) {
                    precisionStep /= 100.f;
                    funcDirection = CONTINUOUS;
                    continue;
                } else {
                    segment.setPoints(position, pos);
                    lastX += precisionStep;
                    funcDirection = dir;
                }
            } while (_visibleArea.contains(pos));
            dirLasted = 0;
        } else {
            segment.setPoints(position, nextPosition);
        }

        segment.setFillColor(cached.func.color);
        cached.lines.join(segment, LineArray::LINE_PRIORITY);

        direction = nextDirection;
        position = nextPosition;
    }
}

void FuncGraph::origin() {
    _absOrigin = _absCenter;
    _scale = GRAPH_SCALE_START;
    _needsRefresh = true;
}

void FuncGraph::move(float dx, float dy) {
    _absOrigin.x += dx;
    _absOrigin.y += dy;
    _needsRefresh = true;
}

void FuncGraph::scale(float delta) {
    const float min = GRAPH_SCALE_MIN;
    const float max = GRAPH_SCALE_MAX;
    if (min <= _scale - delta && _scale - delta <= max) {
        if (_scale <= 1.f) {
            _scale /= std::pow(2.f, delta);
        } else {
            _scale -= delta;
        }
    }

    _needsRefresh = true;
}

sf::Vector2f FuncGraph::getOrigin() const {
    return _absOrigin;
}

sf::Vector2f FuncGraph::getCenter() const {
    return _absCenter;
}

sf::Vector2f FuncGraph::absoluteCoords(float x, float y) {
    sf::Vector2f position(_absOrigin.x + _absCenter.x * x / _scale,
            _absOrigin.y - _absCenter.y * y / _scale);
    return position;
}

sf::Vector2f FuncGraph::absoluteCoords(const sf::Vector2f &relative) {
    return absoluteCoords(relative.x, relative.y);
}

sf::Vector2f FuncGraph::relativeCoords(float x, float y) {
    sf::Vector2f position((x - _absOrigin.x) * _scale / _absCenter.x,
            -(y - _absOrigin.y) * _scale / _absCenter.y);
    return position;
}

sf::Vector2f FuncGraph::relativeCoords(const sf::Vector2f &absolute) {
    return relativeCoords(absolute.x, absolute.y);
}
