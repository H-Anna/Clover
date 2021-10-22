add_subdirectory(balloon)
add_subdirectory(ghost)

add_library(MainProcess mainprocess.cpp)

target_link_libraries(MainProcess PUBLIC Balloon Ghost TokenCollection VariableStore Qt5::Core)
target_include_directories(MainProcess INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
