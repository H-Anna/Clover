add_subdirectory(surface)
add_subdirectory(balloonsurface)
add_library(SurfaceManager surfacemanager.cpp)

target_link_libraries(SurfaceManager PUBLIC Surface BalloonSurface)
target_include_directories(SurfaceManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
