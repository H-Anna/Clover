add_library(FileReader filereader.cpp)

target_link_libraries(FileReader PUBLIC Qt5::Core)
target_include_directories(FileReader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
