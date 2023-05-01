cmake_minimum_required(VERSION 3.24)
project(course0)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(SFML)

file(GLOB GLSL_SHADERS
     RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src
     src/*.vert src/*.frag)

set(SHADER_FILES "")
foreach(SHADER ${GLSL_SHADERS})
    add_custom_command(
        OUTPUT "${SHADER}.o"
        COMMAND objcopy -I binary -O elf64-x86-64 -B i386
                        "${SHADER}" "${CMAKE_CURRENT_BINARY_DIR}/${SHADER}.o"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/${SHADER}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    list(APPEND SHADER_FILES "${SHADER}.o")
endforeach()

file(GLOB SOURCE_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
