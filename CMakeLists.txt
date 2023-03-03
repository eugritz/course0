cmake_minimum_required(VERSION 3.24)
project(project0)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
