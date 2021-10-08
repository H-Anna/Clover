add_library(BalloonWidget balloonwidget.cpp)

target_link_libraries(BalloonWidget PUBLIC Qt5::Core Qt5::Widgets)
target_include_directories(BalloonWidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})