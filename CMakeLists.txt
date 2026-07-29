cmake_minimum_required(VERSION 3.16)
project(solar_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(solar_system
    src/main.cpp
)

target_include_directories(solar_system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(solar_system PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
)