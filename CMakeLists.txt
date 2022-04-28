cmake_minimum_required(VERSION 3.17)

project(qtv)
set(CMAKE_CXX_STANDARD 17)

find_package(raylib CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES src/*.*)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${raylib_LIBRARIES})