#pragma once

#include "Resources.hpp"

template<typename T>
void GlobalResourceManager::load(const std::string &id,
                                        const std::shared_ptr<T> resource) {
    getInstance()->_resources[id] = resource;
}

template<typename T>
SharedResource<T>::SharedResource() {}

template<typename T>
SharedResource<T>::SharedResource(std::shared_ptr<void> raw) : _raw(raw) { }

template<typename T>
SharedResource<T> GlobalResourceManager::ref(const std::string &id) {
    return SharedResource<T>(getInstance()->_resources.at(id));
}

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
