#include "AuthorMenu.h"

#include <iomanip>
#include <sstream>

#include "Course0.h"

const int width = AUTHOR_MENU_ITEM_LENGTH;
const int height = AUTHOR_MENU_ITEM_COUNT;

AuthorMenu::AuthorMenu(sf::RenderTarget *target) : MenuScene(target) {
    _finishing = false;
    setup(width, height);
    setupMenu();
}

void AuthorMenu::setupMenu() {
    std::wstring s1 = L"Курсовая работа по проектной деятельности";
    std::wstring s2 = L"выполнена студентом группы ИВТ-223 Факультета";
    std::wstring s3 = L"Информационных технологий и компьютерных систем";
    std::wstring s4 = L"Гриценко Евгением Вячеславовичем";

    auto center = [&](const std::wstring &s) {
        return width / 2 + s.length() / 2 + 2;
    };

    std::wstringstream ss;
    ss << std::endl;
    ss << std::setw(center(s1)) << s1 << std::endl;
    ss << std::endl;
    ss << std::setw(center(s2)) << s2 << std::endl;
    ss << std::endl;
    ss << std::setw(center(s3)) << s3 << std::endl;
    ss << std::endl;
    ss << std::setw(center(s4)) << s4 << std::endl;
    ss << std::endl;
    ss << std::right << std::setw(width) << L"Омск 2023" << std::endl;
    ss << std::endl;
    _menu[7].setStyle(sf::Text::Italic);

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
            Course0::getInstance()->postEvent(MENU_OPEN);
            _finishing = false;
        }
    }
    return true;
}
