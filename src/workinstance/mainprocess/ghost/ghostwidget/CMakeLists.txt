add_subdirectory(hotspotwidget)
add_library(GhostWidget ghostwidget.cpp)

target_link_libraries(GhostWidget PUBLIC HotspotWidget Frame)
target_include_directories(GhostWidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
