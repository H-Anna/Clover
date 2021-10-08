add_subdirectory(surface)
add_library(SurfaceManager surfacemanager.cpp)

target_link_libraries(SurfaceManager PRIVATE Surface Ghost)
target_include_directories(SurfaceManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
