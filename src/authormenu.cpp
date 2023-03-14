#include "authormenu.h"

#include <iomanip>
#include <sstream>

#include "project0.h"

const int width = AUTHOR_MENU_ITEM_LENGTH;
const int height = AUTHOR_MENU_ITEM_COUNT;

AuthorMenu::AuthorMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void AuthorMenu::setupMenu() {
    std::wstring s1 = L"Расчетно-графическая работа по программированию";
    std::wstring s2 = L"выполнена студентом группы ИВТ-223";
    std::wstring s3 = L"Гриценко Евгением Вячеславовичем";

    auto center = [&](const std::wstring &s) {
        return width / 2 + s.length() / 2;
    };

    std::wstringstream ss;
    ss << std::endl;
    ss << std::setw(center(s1)) << s1 << std::endl;
    ss << std::endl;
    ss << std::setw(center(s2)) << s2 << std::endl;
    ss << std::endl;
    ss << std::setw(center(s3)) << s3 << std::endl;
    ss << std::endl;
    ss << std::right << std::setw(width) << L"Омск 2023" << std::endl;
    ss << std::endl;
    _menu[5].setStyle(sf::Text::Italic);

    _menu.fillFromStream(ss);
}

void AuthorMenu::draw(sf::RenderStates states) {
    MenuScene::draw(states);
}

bool AuthorMenu::handleEvent(const sf::Event &event) {
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
