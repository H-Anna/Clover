add_subdirectory(ghostwidget)
add_library(Ghost ghost.cpp)

target_link_libraries(Ghost PUBLIC GhostWidget Surface)
target_include_directories(Ghost INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
