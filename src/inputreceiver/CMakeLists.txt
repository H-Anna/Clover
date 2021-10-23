add_library(InputReceiver inputreceiver.cpp)

target_link_libraries(InputReceiver PUBLIC Qt5::Core Qt5::Widgets)
target_include_directories(InputReceiver INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
