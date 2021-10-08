add_library(Token token.cpp)

target_link_libraries(Token PUBLIC Qt5::Core)
target_include_directories(Token INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})