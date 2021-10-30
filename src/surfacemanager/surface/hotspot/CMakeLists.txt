add_library(Hotspot hotspot.cpp)

target_link_libraries(Hotspot PUBLIC Qt5::Core)
target_include_directories(Hotspot INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
