#include "tablemenu.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "project0.h"

const int width = TABLE_MENU_ITEM_LENGTH;
const int height = TABLE_MENU_ITEM_COUNT;

const float begin = 2.f, end = 4.f;
const std::size_t iters = 12;

TableMenu::TableMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void TableMenu::setupMenu() {
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
    for (std::size_t n = 1; n <= 12; n++, x += step) {
        float f1 = std::pow(2, x)*std::log10(x) - std::pow(3, x)*std::log10(x);
        float f2 = 1.f / std::tan(x);

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
            Project0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}
