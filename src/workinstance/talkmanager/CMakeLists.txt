add_subdirectory(tokencollection)
add_library(TalkManager talkmanager.cpp)

target_link_libraries(TalkManager PUBLIC TokenCollection)
target_include_directories(TalkManager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
