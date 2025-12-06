cmake_minimum_required(VERSION 3.10)
project(QOsis
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Parsing Library and Utilities"
)

include(GNUInstallDirs)  # REQUIRED TO INSTALL PKGCONFIG TO PROPER DIR!
include(CTest)

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h @ONLY)

add_compile_options(-DQT_DEBUG=ON)
set(BUILD_LIBRARY OFF CACHE BOOL "Build OSIS library component")
set(BUILD_CLI OFF CACHE BOOL "Build OSIS CLI component")
set(BUILD_GUI OFF CACHE BOOL "Build OSIS GUI component")
set(ONLY_LIBRARY OFF CACHE BOOL "Build only the OSIS library component")
set(ONLY_CLI OFF CACHE BOOL "Build only the OSIS CLI component")
set(ONLY_GUI OFF CACHE BOOL "Build only the OSIS GUI component")

if(BUILD_LIBRARY)
    list(APPEND QOSIS_BUILDS lib)
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


if (APPLE)
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
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
    )
endif()

foreach(QOSIS_BUILD_TYPE IN LISTS QOSIS_BUILDS)
    message(STATUS "Building project component ${QOSIS_BUILD_TYPE}")
    #include_directories(${QOSIS_BUILD_TYPE})
endforeach(QOSIS_BUILD_TYPE)

list(APPEND APP_SOURCES
    about.cpp
    main.cpp
    mainwindow.cpp
    preferences.cpp)

list(APPEND APP_HEADERS
    about.h
    cocoainitializer.h
    mainwindow.h
    preferences.h)

list(APPEND APP_UIS
    about.ui
    preferences.ui
    mainwindow.ui)

list(APPEND APP_RES)

list(APPEND APP_OTHER)

if (APPLE)
    set(APP_ICON "${MACOSX_BUNDLE_ICON_FILE}")
    list(APPEND APP_OTHER ${APP_ICON})
    list(APPEND APP_SOURCES cocoainitializer.mm)
    list(APPEND APP_HEADERS cocoainitializer.h)
    add_custom_target(OTHER_FILES SOURCES ${APP_OTHER})
    set_property(SOURCE ${APP_ICON} PROPERTY MACOSX_PACKAGE_LOCATION
            ${MACOSX_BUNDLE_ICON_FILE})
    file(COPY ${APP_ICON} DESTINATION
             ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
            ${OTHER_FILES}
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            ${APP_HEADERS}
            ${APP_SOURCES}
            ${APP_UIS}
            ${APP_UI_HEADERS}
            ${APP_RES}
    )
    target_sources(${PROJECT_NAME} PRIVATE
            ${APP_OTHER}
    )
    set_source_files_properties(
            ${APP_OTHER}
            PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources/
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
            BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER org.peondevelopments.qosis
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
             "-Wl,-F/Library/Frameworks")
    target_link_libraries(${PROJECT_NAME} stdc++
            "-framework Cocoa"
            objc
    )
else()
    add_executable(${PROJECT_NAME}
            ${APP_OTHER}
            main.cpp
            ${APP_HEADERS}
            ${APP_SOURCES}
            ${APP_UIS}
            ${APP_UI_HEADERS}
            ${APP_RES}
        )
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Test)
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE .. )
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/)
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/${PROJECT_BINARY_DIR}/${PROJECT_NAME}_autogen/include/)



if(APPLE)
        find_package(Qt5 REQUIRED MacExtras)
        target_link_libraries(${PROJECT_NAME} Qt5::MacExtras)
elseif(MSVC)
        find_package(Qt5 HINTS "$ENV{QT5_DIR}" COMPONENTS Core Quick REQUIRED)
        set(CMAKE_PREFIX_PATH "C:\\Qt\\5.3.1\\5.3\\msvc2013_opengl")
        set(Qt5_DIR "C:/Qt/Qt5.3.2/5.3/msvc2013_64_opengl/")
        find_package(Qt5 COMPONENTS WinExtras REQUIRED)
        target_link_libraries(${PROJECT_NAME} Qt5::WinExtras)
endif()
