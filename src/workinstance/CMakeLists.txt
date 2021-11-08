add_subdirectory(filereader)
add_subdirectory(mainprocess)
add_subdirectory(surfacemanager)
add_subdirectory(talkmanager)
add_subdirectory(variablestore)
add_subdirectory(soundemitter)

add_library(WorkInstance workinstance.cpp)

target_include_directories(WorkInstance INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(WorkInstance
        FileReader
        MainProcess
        SurfaceManager
        TalkManager
        VariableStore
        SoundEmitter
)
