#include "mandelbrot.h"

#include <cmath>

#include "project0.h"

using namespace mandelbrot;

Real stepX, stepY;
const int iters = 500;

sf::Color colorFromResult(unsigned int res);

Mandelbrot::Mandelbrot() {}
Mandelbrot::Mandelbrot(sf::Vector2i size, sf::Vector2<Real> origin,
                       Real radius) {
    create(size, origin, radius);
}

Mandelbrot::Mandelbrot(sf::Vector2i size, sf::Vector2<Real> begin,
                       sf::Vector2<Real> end) {
    create(size, begin, end);
}

Mandelbrot::~Mandelbrot() {
    if (_done) delete _done;
    if (_data) delete _data;
}

void Mandelbrot::create(sf::Vector2i size, sf::Vector2<Real> origin,
                        Real radius) {
    _size = size;
    _begin.x = origin.x - radius;
    _begin.y = origin.y + radius;
    _end.x = origin.x + radius;
    _end.y = origin.y - radius;

    stepX = (_end.x - _begin.x) / size.x;
    stepY = (_end.y - _begin.y) / size.y;

    _image.create(_size.x, _size.y);
    reset();
}

void Mandelbrot::create(sf::Vector2i size, sf::Vector2<Real> begin,
                        sf::Vector2<Real> end) {
    _size = size;
    _begin = begin;
    _end = end;

    stepX = (_end.x - _begin.x) / size.x;
    stepY = (_end.y - _begin.y) / size.y;

    _image.create(_size.x, _size.y);
    reset();
}

void Mandelbrot::reset() {
    if (_done) delete _done;
    if (_data) delete _data;
    _done = new unsigned[_size.x * _size.y];
    _data = new unsigned[_size.x * _size.y];

    _rendered = false;
    _filled = false;
    _fill_step = 0;

    std::queue<unsigned>().swap(_queue);
    for (unsigned x = 0; x < _size.x; x++) {
        _queue.push(x);
        _queue.push((_size.y - 1) * _size.x + x);
    }
    for (unsigned y = 1; y < _size.y - 1; y++) {
        _queue.push(y * _size.x);
        _queue.push((y + 1) * _size.x - 1);
    }
}

sf::Vector2i Mandelbrot::getSize() const {
    return _size;
}

sf::Vector2<Real> Mandelbrot::getFirstPoint() const {
    return _begin;
}

sf::Vector2<Real> Mandelbrot::getSecondPoint() const {
    return _end;
}

bool Mandelbrot::isRendered() const {
    return _rendered;
}

bool Mandelbrot::isFilled() const {
    return _filled;
}

void Mandelbrot::stepRender() {
    if (!_rendered && !_queue.empty()) {
        scan(_queue.front());
        _queue.pop();
        return;
    }

    _rendered = true;
}

void Mandelbrot::stepFill() {
    if (_filled || _fill_step >= _size.x * _size.y - 1) {
        _filled = true;
        return;
    }

    unsigned i = 0, j = _fill_step;
    for (; i < _size.x; i++) {
        if (_done[i + j] & LOADED && !(_done[i + j + 1] & LOADED)) {
            unsigned int x1 = (i + j) % _size.x, y1 = (i + j) / _size.x;
            unsigned int x2 = (i + j + 1) % _size.x, y2 = (i + j + 1) / _size.x;
            sf::Color clr = _image.getPixel(x1, y1);
            _image.setPixel(x2, y2, clr);
            _done[i + j + 1] |= LOADED;
        }
    }

    _fill_step += i;
}

void Mandelbrot::render() {
    sf::Color color;
    int imageX = 0, imageY = 0;
    for (Real currX = _begin.x; currX <= _end.x; currX += stepX, imageX++) {
        imageY = 0;
        while (imageX >= _size.x)
            imageX--;
        for (Real currY = _begin.y; currY <= _end.y; currY += stepX, imageY++) {
            while (imageY >= _size.y)
                imageY--;

            Complex<Real> curr;
            int iter = iterate(currX, currY);
            _image.setPixel(imageX, imageY, colorFromResult(iter));
        }
    }

    _rendered = true;
}

void Mandelbrot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromImage(_image);
    sprite.setTexture(texture);
    target.draw(sprite, states);
}

int Mandelbrot::load(unsigned nth, unsigned x, unsigned y) {
    if (_done[nth] & LOADED) return _data[nth];

    int iter = iterate(nth, x, y);
    _image.setPixel(x, y, colorFromResult(iter));

    _done[nth] |= LOADED;
    _data[nth] = iter;
    return iter;
}

void Mandelbrot::push(unsigned nth) {
    if (_done[nth] & QUEUED) return;
    _done[nth] |= QUEUED;
    _queue.push(nth);
}

void Mandelbrot::scan(unsigned nth) {
    unsigned x = nth % _size.x, y = nth / _size.x;
    int center = load(nth, x, y);
    bool ll = x >= 1, rr = x < _size.x - 1;
    bool uu = y >= 1, dd = y < _size.y - 1;

    bool l = ll && load(nth - 1, x - 1, y) != center;
    bool r = rr && load(nth + 1, x + 1, y) != center;
    bool u = uu && load(nth - _size.x, x, y - 1) != center;
    bool d = dd && load(nth + _size.x, x, y + 1) != center;

    if ((ll && uu) && (l || u)) push(nth - _size.x - 1);
    if ((rr && uu) && (r || u)) push(nth - _size.x + 1);
    if ((ll && dd) && (l || d)) push(nth + _size.x - 1);
    if ((rr && dd) && (r || d)) push(nth + _size.x + 1);

    if (l) push(nth - 1);
    if (r) push(nth + 1);
    if (u) push(nth - _size.x);
    if (d) push(nth + _size.x);
}

int Mandelbrot::iterate(Real x, Real y) {
    Complex<Real> curr;
    int i = 0;
    for (; i < iters; i++) {
        if (curr.module_sqr() >= 4.0) break;
        Real re = curr.re * curr.re - curr.im * curr.im + x;
        Real im = curr.re * curr.im + curr.im * curr.re + y;
        curr.re = re;
        curr.im = im;
    }
    return i;
}

int Mandelbrot::iterate(unsigned nth, unsigned col, unsigned row) {
    Complex<Real> curr;
    Real x = _begin.x + col * stepX;
    Real y = _begin.y + row * stepY;
    return iterate(x, y);
}

sf::Color colorFromResult(unsigned res) {
    sf::Color clr = sf::Color::Black;
    clr.r = clr.r + 10 * res < 0x100 ? clr.r + 5 * res : 0xff;
    clr.g = clr.g + 4 * res < 0x100 ? clr.g + 5 * res : 0xff;
    clr.b = clr.b + 2 * res < 0x100 ? clr.b + 5 * res : 0xff;
    return clr;
}
