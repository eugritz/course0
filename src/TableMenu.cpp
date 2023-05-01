#include "TableMenu.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "Course0.h"

const int width = TABLE_MENU_ITEM_LENGTH;
const int height = TABLE_MENU_ITEM_COUNT;
const sf::Color maxColor = sf::Color::Red;
const sf::Color minColor = sf::Color(80, 80, 255);

const float begin = 2.f, end = 4.f;
const std::size_t iters = 12;

TableMenu::TableMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void TableMenu::setupMenu() {
    setupTable();

    _menu.fillItem(L"");
    _menu.fillItem(L" + максимальное");
    _menu.fillItem(L" - минимальное");
}

void TableMenu::setupTable() {
    const int cols = 4;
    const int cellWidth = width / 4 - 3;
    const float step = (end - begin) / (iters - 1);

    const std::wstring f1 = L"F1(x) = 2^x*log(x) - 3^x*log(x)";
    const std::wstring f2 = L"F2(x) = ctg(x)";

    std::wstringstream ss;
    ss << std::right;
    ss << std::setw(width) << f1 << std::endl;
    ss << std::wstring(width - f1.length(), L' ') << f2 << std::endl;
    ss << std::endl;

    ss << std::setprecision(4) << std::fixed;
    ss << L"┌─" << std::wstring(cellWidth, L'─');
    for (std::size_t i = 0; i < cols - 1; i++)
        ss << L"─┬─" << std::wstring(cellWidth, L'─');
    ss << L"─┐" << std::endl;

    ss << std::left;
    ss << L"│ " << std::setw(cellWidth) << L"№";
    ss << L" │ " << std::setw(cellWidth) << "X";
    ss << L" │ " << std::setw(cellWidth) << "F1";
    ss << L" │ " << std::setw(cellWidth) << "F2";
    ss << L" │" << std::endl;

    ss << L"├─" << std::wstring(cellWidth, L'─');
    ss << L"─┼─" << std::wstring(cellWidth, L'─');
    ss << L"─┼─" << std::wstring(cellWidth, L'─');
    ss << L"─┼─" << std::wstring(cellWidth, L'─');
    ss << L"─┤" << std::endl;

    float x = 2.f;
    std::size_t f1Min = 0;
    std::size_t f2Min = 0;
    std::size_t f1Max = 0;
    std::size_t f2Max = 0;
    float table[2][iters];
    for (std::size_t n = 1; n <= iters; n++, x += step) {
        float f1 = std::pow(2, x)*std::log10(x) - std::pow(3, x)*std::log10(x);
        float f2 = 1.f / std::tan(x);
        table[0][n - 1] = f1;
        table[1][n - 1] = f2;
        if (f1 > table[0][f1Max]) f1Max = n-1;
        if (f2 > table[1][f2Max]) f2Max = n-1;
        if (f1 < table[0][f1Min]) f1Min = n-1;
        if (f2 < table[1][f2Min]) f2Min = n-1;

        ss << std::right;
        ss << L"│ " << std::setw(cellWidth) << n;
        ss << L" │ " << std::setw(cellWidth) << x;
        ss << L" │ " << std::setw(cellWidth) << f1;
        ss << L" │ " << std::setw(cellWidth) << f2;
        ss << L" │" << std::endl;
    }

    ss << L"└─" << std::wstring(cellWidth, L'─');
    for (std::size_t i = 0; i < cols - 1; i++)
        ss << L"─┴─" << std::wstring(cellWidth, L'─');
    ss << L"─┘" << std::endl;

    _menu.fillFromStream(ss);

    sf::String text = _menu[6+f1Min].getString();
    text[25] = '-';
    _menu[6+f1Min].setString(text);

    text = _menu[6+f2Min].getString();
    text[37] = '-';
    _menu[6+f2Min].setString(text);

    text = _menu[6+f1Max].getString();
    text[25] = '+';
    _menu[6+f1Max].setString(text);

    text = _menu[6+f2Max].getString();
    text[37] = '+';
    _menu[6+f2Max].setString(text);
}

void TableMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool TableMenu::handleEvent(const sf::Event &event) {
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
