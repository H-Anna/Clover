add_library(VariableStore variablestore.cpp)

target_link_libraries(VariableStore PRIVATE Qt5::Core)
target_include_directories(VariableStore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
