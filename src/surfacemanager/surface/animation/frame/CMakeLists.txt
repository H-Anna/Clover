add_library(Frame frame.cpp)

target_link_libraries(Frame PUBLIC Qt5::Core)
target_include_directories(Frame INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
