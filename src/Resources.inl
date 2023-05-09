#pragma once

#include "Resources.hpp"

template<typename T>
SharedResource<T> GlobalResourceManager::load(const std::string &id,
                                              const std::shared_ptr<T> resource) {
    getInstance()->_resources[id] = resource;
    return SharedResource<T>(resource);
}

template<typename T>
SharedResource<T> GlobalResourceManager::ref(const std::string &id) {
    GlobalResourceManager *manager = getInstance();

    std::unordered_map<std::string, std::shared_ptr<void>>::iterator it;
    if ((it = manager->_resources.find(id)) == manager->_resources.end()) {
        return SharedResource<T>();
    }

    return SharedResource<T>(it->second);
}

template<typename T>
SharedResource<T> GlobalResourceManager::refOr(const std::string &id,
            std::function<std::shared_ptr<T>()> callback) {
    GlobalResourceManager *manager = getInstance();

    std::unordered_map<std::string, std::shared_ptr<void>>::iterator it;
    if ((it = manager->_resources.find(id)) == manager->_resources.end()) {
        return GlobalResourceManager::load(id, callback());
    }

    return SharedResource<T>(it->second);
}

template<typename T>
SharedResource<T>::SharedResource() {}

template<typename T>
SharedResource<T>::SharedResource(std::shared_ptr<void> raw) : _raw(raw) { }

template<typename T>
SharedResource<T>::operator bool() const {
    return !!_raw;
}

template<typename T>
const T *SharedResource<T>::operator->() const {
    return _raw.get();
}

template<typename T>
T *SharedResource<T>::operator->() {
    return (T *)_raw.get();
}

template<typename T>
const T *SharedResource<T>::operator*() const {
    return _raw.get();
}

template<typename T>
T *SharedResource<T>::operator*() {
    return (T *)_raw.get();
}

template<typename T>
long SharedResource<T>::use_count() const {
    return _raw.use_count();
}
