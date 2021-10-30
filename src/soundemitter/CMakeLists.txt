add_library(SoundEmitter soundemitter.cpp)

target_link_libraries(SoundEmitter PUBLIC Qt5::Core Qt5::Multimedia)
target_include_directories(SoundEmitter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
