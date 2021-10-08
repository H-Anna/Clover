add_subdirectory(filereader)
add_subdirectory(mainprocess)
add_subdirectory(surfacemanager)
add_subdirectory(talkmanager)

add_executable(GhostTest main.cpp)
target_link_libraries(GhostTest
	FileReader
	MainProcess
	SurfaceManager
	TalkManager
)