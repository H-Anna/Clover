add_subdirectory(textarea)
add_library(BalloonWidget balloonwidget.cpp)

target_link_libraries(BalloonWidget PUBLIC TextArea)
target_include_directories(BalloonWidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})