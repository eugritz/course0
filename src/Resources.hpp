#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#define BINARY_RESOURCE(name)                                        \
({                                                                   \
    extern char _binary_##name##_start;                              \
    extern char _binary_##name##_end;                                \
    binary_resource(&_binary_##name##_start, &_binary_##name##_end); \
})

inline std::string binary_resource(char *begin, char *end) {
    std::string content(begin, end - begin);
    return content;
}

template<typename T>
class SharedResource;

class GlobalResourceManager {
    static GlobalResourceManager *_instance;
    std::unordered_map<std::string, std::shared_ptr<void>> _resources;

    static GlobalResourceManager *getInstance();

    GlobalResourceManager();
    GlobalResourceManager(const GlobalResourceManager &);
    GlobalResourceManager& operator=(GlobalResourceManager &);

public:
    template<typename T>
    static void load(const std::string &id, const std::shared_ptr<T> resource);

    template<typename T>
    static SharedResource<T> ref(const std::string &id);
};

template<typename T>
class SharedResource {
    std::shared_ptr<void> _raw;

    friend class GlobalResourceManager;

    SharedResource(std::shared_ptr<void> raw);

public:
    SharedResource();

    explicit operator bool() const;

    const T *operator->() const;
    T *operator->();
    const T *operator*() const;
    T *operator*();

    long use_count() const;
};

#include "Resources.inl"
