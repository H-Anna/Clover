add_subdirectory(animation)
add_library(Surface surface.cpp)

target_link_libraries(Surface PUBLIC Animation)
target_include_directories(Surface INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})