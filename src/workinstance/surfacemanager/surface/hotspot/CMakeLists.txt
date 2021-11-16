add_subdirectory(hotspotvariable)

add_library(Hotspot hotspot.cpp)

target_link_libraries(Hotspot PUBLIC HotspotVariable)
target_include_directories(Hotspot INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
