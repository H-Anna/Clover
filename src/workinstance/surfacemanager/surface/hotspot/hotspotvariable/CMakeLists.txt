add_library(HotspotVariable hotspotvariable.cpp)

target_link_libraries(HotspotVariable PUBLIC Qt5::Core)
target_include_directories(HotspotVariable INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
