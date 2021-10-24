add_subdirectory(filereader)
add_subdirectory(mainprocess)
add_subdirectory(surfacemanager)
add_subdirectory(talkmanager)
add_subdirectory(variablestore)
add_subdirectory(inputreceiver)
add_subdirectory(soundemitter)

add_executable(Clover main.cpp)
target_link_libraries(Clover
        FileReader
        MainProcess
        SurfaceManager
        TalkManager
        VariableStore
        InputReceiver
        SoundEmitter
)
