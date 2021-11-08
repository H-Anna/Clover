add_subdirectory(frame)
add_library(Animation animation.cpp)

target_link_libraries(Animation PUBLIC Frame)
target_include_directories(Animation INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})