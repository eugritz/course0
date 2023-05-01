#include "IntegralMenu.h"

#include <cmath>

#include "Project0.h"

const int width = INTEGRAL_MENU_ITEM_LENGTH;
const int height = INTEGRAL_MENU_ITEM_COUNT;

float func2(float x) {
    return std::cbrt(x + 1);
}

IntegralMenu::IntegralMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void IntegralMenu::setupMenu() {
    _menu.fillItem(L"Интегрирование функции ³√(x+1)");
    _menu.fillItem("");

    rectanglesMethodMenu();
    _menu[2].setStyle(sf::Text::Underlined);
    _menu[5].setStyle(sf::Text::Bold);

    trapezoidMethodMenu();
    _menu[7].setStyle(sf::Text::Underlined);
    _menu[10].setStyle(sf::Text::Bold);
}

void IntegralMenu::rectanglesMethodMenu() {
    const float a = -1, b = 3;
    const int n = 100;
    float solution = rectangle(a, b, n, func2);

    std::wstringstream ss;
    ss << L"Метод прямоугольников:" << std::endl;
    ss << L"— Интервал: [" << a << ", " << b << "]" << std::endl; 
    ss << L"— Кол-во итераций: n=" << n << std::endl;
    ss << L"Определенный интеграл: " << solution << std::endl;
    ss << std::endl;
    _menu.fillFromStream(ss);
}

void IntegralMenu::trapezoidMethodMenu() {
    const float a = -1, b = 3;
    const int n = 100;
    float solution = trapezoid(a, b, n, func2);

    std::wstringstream ss;
    ss << L"Метод трапеций:" << std::endl;
    ss << L"— Интервал: [" << a << ", " << b << "]" << std::endl; 
    ss << L"— Кол-во итераций: n=" << n << std::endl;
    ss << L"Определенный интеграл: " << solution << std::endl;
    ss << std::endl;
    _menu.fillFromStream(ss);
}

void IntegralMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool IntegralMenu::handleEvent(const sf::Event &event) {
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
            Project0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}

float IntegralMenu::rectangle(float a, float b, float n,
                              std::function<float(float)> func) {
    float area = 0.f;
    float h = (b - a) / n;
    for (float x = a; x < b + h / 2.f; x += h) {
        area += func(x);
    }
    return area * h;
}

float IntegralMenu::trapezoid(float a, float b, float n,
                              std::function<float(float)> func) {
    float area = func(a) + func(b);
    float h = (b - a) / n;
    for (float x = a + h; x < b - h / 2.f; x += h) {
        area += 2.f * func(x);
    }
    return h / 2.f * area;
}
