cmake_minimum_required(VERSION 3.10)
project(qosis-gui
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Graphical User Interface"
)


include(GNUInstallDirs)  # REQUIRED TO INSTALL PKGCONFIG TO PROPER DIR!
include(CTest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

message(STATUS "Building OSIS GUI in ${CMAKE_CURRENT_LIST_DIR}...")


find_package(Qt5 REQUIRED
    Core
    Gui
    Widgets
    Test
)

add_compile_options(-v)

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_LIST_DIR}/src/version.h.in
    ${CMAKE_CURRENT_LIST_DIR}/src/version.h @ONLY)

list(APPEND APP_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/about.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/mainwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/preferences.cpp)

list(APPEND APP_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/about.h
    ${CMAKE_CURRENT_LIST_DIR}/src/cocoainitializer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/mainwindow.h
    ${CMAKE_CURRENT_LIST_DIR}/src/preferences.h)

list(APPEND APP_UIS
    ${CMAKE_CURRENT_LIST_DIR}/src/about.ui
    ${CMAKE_CURRENT_LIST_DIR}/src/preferences.ui
    ${CMAKE_CURRENT_LIST_DIR}/src/mainwindow.ui)

list(APPEND APP_RES)

list(APPEND APP_OTHER)

find_package(qosis CONFIG REQUIRED 1.0.0.0)

if (APPLE)
    set(APP_ICON "${MACOSX_BUNDLE_ICON_FILE}")
    list(APPEND APP_OTHER ${APP_ICON})
    list(APPEND APP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/cocoainitializer.mm)
    list(APPEND APP_HEADERS ${CMAKE_CURRENT_LIST_DIR}/src/cocoainitializer.h)
    add_custom_target(OTHER_FILES SOURCES ${APP_OTHER})
    set_property(SOURCE ${APP_ICON} PROPERTY MACOSX_PACKAGE_LOCATION
            ${MACOSX_BUNDLE_ICON_FILE})
    file(COPY ${APP_ICON} DESTINATION
             ${CMAKE_CURRENT_BINARY_DIR})
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE
            ${OTHER_FILES}
            ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
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
            ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
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
target_link_libraries(${PROJECT_NAME} qosis)


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
