cmake_minimum_required(VERSION 3.10)

if (APPLE)
    message(STATUS "Using clang compiler")
    set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "CMake C Compiler")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "CMake C++ Compiler")
endif()

project(QOsis
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Parsing Library and Utilities"
)

add_compile_options(-DQT_DEBUG=ON)

include(GNUInstallDirs)  # REQUIRED TO INSTALL PKGCONFIG TO PROPER DIR!
include(CTest)
set(BUILD_LIBRARY OFF CACHE BOOL "Build OSIS library component")
set(BUILD_CLI OFF CACHE BOOL "Build OSIS CLI component")
set(BUILD_GUI OFF CACHE BOOL "Build OSIS GUI component")
set(ONLY_LIBRARY OFF CACHE BOOL "Build only the OSIS library component")
set(ONLY_CLI OFF CACHE BOOL "Build only the OSIS CLI component")
set(ONLY_GUI OFF CACHE BOOL "Build only the OSIS GUI component")


if(BUILD_LIBRARY)
    list(APPEND QOSIS_BUILDS lib)
    list(APPEND QOSIS_BUILDS tests)
    message(STATUS "APPENDING LIBRARY")
endif()

if(BUILD_CLI)
    list(APPEND QOSIS_BUILDS cli)
    message(STATUS "APPENDING CLI")
endif()

if(BUILD_GUI)
    list(APPEND QOSIS_BUILDS gui)
    message(STATUS "APPENDING GUI")
endif()

# Now set the list if an ONLY is found, hierarchy is: Gui -> CLI -> Library (highest)
if(ONLY_CLI)
    set(QOSIS_BUILDS cli;)
endif()
if(ONLY_GUI)
    set(QOSIS_BUILDS gui;)
endif()
if(ONLY_LIBRARY)
    set(QOSIS_BUILDS lib;)
endif()



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

### DEPENDENCIES ###

find_package(Qt5 REQUIRED
    Core
    Gui
    Widgets
    Xml
    Test
)

# If no declaratives are set, we build everything. Determine if something is set
set(QOSIS_BUILD_LEN 0)
list(LENGTH QOSIS_BUILDS QOSIS_BUILD_LEN)

if(${QOSIS_BUILD_LEN} GREATER 0)
    message(STATUS "There is something defined in QOSIS_BUILDS ${QOSIS_BUILDS}")
else()
    list(APPEND QOSIS_BUILDS
        lib
        cli
        gui
        tests
    )
endif()



foreach(QOSIS_BUILD_TYPE IN LISTS QOSIS_BUILDS)
    message(STATUS "Building project component ${QOSIS_BUILD_TYPE}")
    include(${CMAKE_CURRENT_SOURCE_DIR}/${QOSIS_BUILD_TYPE}/CMakeLists.txt)
endforeach(QOSIS_BUILD_TYPE)
