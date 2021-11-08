add_library(TextArea textarea.cpp)

target_link_libraries(TextArea PUBLIC Qt5::Core Qt5::Widgets VariableStore)
target_include_directories(TextArea INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
