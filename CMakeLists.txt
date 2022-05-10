cmake_minimum_required(VERSION 3.17)

project(ntl)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)

set(DHELLOIMGUI_USE_SDL_OPENGL3 ON CACHE BOOL "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${HELLOIMGUI_BASEPATH}/hello_imgui_cmake)

include(hello_imgui_add_app)

find_package(simdjson CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES src/*.*)
hello_imgui_add_app(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE simdjson::simdjson fmt::fmt)