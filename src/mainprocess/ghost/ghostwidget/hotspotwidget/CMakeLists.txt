add_library(HotspotWidget hotspotwidget.cpp)

target_link_libraries(HotspotWidget PUBLIC Qt5::Core Qt5::Widgets Hotspot VariableStore)
target_include_directories(HotspotWidget INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
