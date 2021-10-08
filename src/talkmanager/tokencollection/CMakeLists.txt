add_subdirectory(token)
add_library(TokenCollection tokencollection.cpp)

target_link_libraries(TokenCollection PUBLIC Token)
target_include_directories(TokenCollection INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})