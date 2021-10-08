add_library(GhostWidget ghostwidget.cpp)

target_link_libraries(GhostWidget PUBLIC Qt5::Core Qt5::Widgets)
target_include_directories(GhostWidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})