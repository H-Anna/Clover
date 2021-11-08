add_subdirectory(workinstance)

add_executable(Clover main.cpp)
target_link_libraries(Clover
        WorkInstance
)
