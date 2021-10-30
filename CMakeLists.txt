cmake_minimum_required(VERSION 3.5)

project(Clover LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src/common)

add_subdirectory(src)
