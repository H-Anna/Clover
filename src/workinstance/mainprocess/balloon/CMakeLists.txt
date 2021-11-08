add_subdirectory(balloonwidget)
add_library(Balloon balloon.cpp)

target_link_libraries(Balloon PUBLIC BalloonWidget BalloonSurface)
target_include_directories(Balloon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
