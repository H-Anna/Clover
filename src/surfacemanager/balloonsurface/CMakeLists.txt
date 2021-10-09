add_library(BalloonSurface balloonsurface.cpp)

target_link_libraries(BalloonSurface PUBLIC Qt5::Core)
target_include_directories(BalloonSurface
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
