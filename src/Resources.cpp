#include "Resources.hpp"

GlobalResourceManager *GlobalResourceManager::_instance;

GlobalResourceManager::GlobalResourceManager() { }

GlobalResourceManager *GlobalResourceManager::getInstance() {
    if (_instance == nullptr)
        _instance = new GlobalResourceManager();
    return _instance;
}
