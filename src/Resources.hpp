#pragma once

#include <string>

#define RESOURCE(name)                                             \
({                                                                 \
    extern char _binary_##name##_start;                            \
    extern char _binary_##name##_end;                              \
    load_resource(&_binary_##name##_start, &_binary_##name##_end); \
})

inline std::string load_resource(char *begin, char *end) {
    std::string content(begin, end - begin);
    return content;
}
