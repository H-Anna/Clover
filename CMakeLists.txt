cmake_minimum_required(VERSION 3.5)

project(GhostTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(GhostTest
    main.cpp
    ghostwidget.cpp
    balloonwidget.cpp
    surface.cpp
    mainprocess.cpp
    talkmanager.cpp
    surfacemanager.cpp
    filereader.cpp
    tokencollection.cpp
    token.cpp
    ghost.cpp
    balloon.cpp
    animation.cpp
    frame.cpp
)

target_link_libraries(GhostTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
