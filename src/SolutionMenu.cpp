#include "SolutionMenu.h"

#include <sstream>

#include "Course0.h"

bool sign(float num);

const int width = SOLUTION_MENU_ITEM_LENGTH;
const int height = SOLUTION_MENU_ITEM_COUNT;

float func1(float x) {
    return 2*x*x*x - 3*x*x - 4;
}

SolutionMenu::SolutionMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void SolutionMenu::setupMenu() {
    _menu.fillItem(L"Решение уравнения 2x³-3x²-4=0");
    _menu.fillItem("");

    bisectMethodMenu();
    _menu[2].setStyle(sf::Text::Underlined);
    _menu[5].setStyle(sf::Text::Bold);

    chordsMethodMenu();
    _menu[7].setStyle(sf::Text::Underlined);
    _menu[10].setStyle(sf::Text::Bold);
}

void SolutionMenu::bisectMethodMenu() {
    const float a = -1, b = 4;
    const float e = 0.001;
    float solution = bisect(a, b, e, func1);

    std::wstringstream ss;
    ss << L"Метод половинного деления (дихотомия):" << std::endl;
    ss << L"— Интервал: [" << a << ", " << b << "]" << std::endl; 
    ss << L"— Точность: e=" << e << std::endl;
    ss << L"Корень уравнения: " << solution << std::endl;
    ss << std::endl;
    _menu.fillFromStream(ss);
}

void SolutionMenu::chordsMethodMenu() {
    const float a = -1, b = 4;
    const float e = 0.001;
    float solution = chords(b, a, e, func1);

    std::wstringstream ss;
    ss << L"Метод хорд:" << std::endl;
    ss << L"— Интервал: [" << a << ", " << b << "]" << std::endl; 
    ss << L"— Точность: e=" << e << std::endl;
    ss << L"Корень уравнения: " << solution << std::endl;
    _menu.fillFromStream(ss);
} 

void SolutionMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool SolutionMenu::handleEvent(const sf::Event &event) {
    if (!MenuScene::handleEvent(event))
        return true;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter ||
            event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Space) {
            _finishing = true;
        }
    } else if (event.type == sf::Event::KeyReleased) {
        if (_finishing) {
            Course0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}

float SolutionMenu::bisect(float a, float b, float e,
                           std::function<float(float)> func) {
    float m = (a + b) / 2.f;
    float y = func(m);
    if (-e < y && y < e)
        return m;
    return (sign(func(a)) != sign(func(m)))
        ? bisect(a, m, e, func)
        : bisect(m, b, e, func);
}

float SolutionMenu::chords(float x0, float x1, float e,
                           std::function<float(float)> func) {
    float x2 = x1 - (x1 - x0) / (func(x1) - func(x0)) * func(x1);
    if (std::abs(x2 - x1) < e)
        return x2;
    return chords(x0, x2, e, func);
}

bool sign(float num) {
    return num >= 0.f;
}
