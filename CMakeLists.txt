cmake_minimum_required(VERSION 3.5)

project(Clover LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Multimedia REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/src/common)

add_subdirectory(src)

# Setting up CPack

install(TARGETS Clover DESTINATION .)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/ DESTINATION data)

# Installer for Unix

if(UNIX)

    if (${CPACK_BINARY_DEB})
        message("Ubuntu, x64 only")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "H-Anna")
        set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt5-default")

    elseif(${CPACK_BINARY_RPM})
        message("CentOS, x64 only")
        set(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
        set(CPACK_RPM_PACKAGE_REQUIRES "qt5-qttools")

    endif()

# Installer for Windows

elseif(WIN32)

    # x64
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/x64/ DESTINATION .)
    # x86
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
        install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/x86/ DESTINATION .)
    endif()

endif()

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/USER-README.md")
set(CPACK_PACKAGE_VENDOR "H-Anna")

include(CPack)
