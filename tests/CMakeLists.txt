cmake_minimum_required(VERSION 3.10)

if (APPLE)
    set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "CMake C Compiler")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "CMake C++ Compiler")
endif()

project(qosis-tests
        VERSION 0.0.2.0
        LANGUAGES C CXX
        DESCRIPTION "Tests for ensuring quality of the osis format library"
)

include(GNUInstallDirs)
include(CTest)

set(QT_DEFAULT_MAJOR_VERSION "6" CACHE STRING "Qt Version defaults to 6 (latest)")

find_package(Qt${QT_DEFAULT_MAJOR_VERSION} NAMES Qt5 Qt6 REQUIRED COMPONENTS
    Core
    Xml
    Test
)

if(${QT_DEFAULT_MAJOR_VERSION} STREQUAL "6")
    find_package(Qt6 REQUIRED COMPONENTS
        Core5Compat
    )
else()
    find_package(Qt5 REQUIRED COMPONENTS
        XmlPatterns
    )
endif()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

message(STATUS "Debugging flag enabled: ${QT_DEBUG}")


list(APPEND TEST_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_validator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_exporter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_importer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_reader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_writer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_meta.cpp
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/singletonbook.cpp
)

list(APPEND TEST_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_validator.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_exporter.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_importer.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_reader.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_writer.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_meta.h
    ${CMAKE_CURRENT_LIST_DIR}/suite/test_xml_json.h
    ${CMAKE_CURRENT_LIST_DIR}/singletonbook.h
    ${CMAKE_CURRENT_LIST_DIR}/variables.h
)

list(APPEND TEST_OTHER
    ${CMAKE_CURRENT_LIST_DIR}/qosis-testfile.xml
    ${CMAKE_CURRENT_LIST_DIR}/qosis-files.qrc
)

message(STATUS "${CMAKE_CURRENT_LIST_DIR}/../lib/src")
include_directories(${CMAKE_CURRENT_LIST_DIR}/../lib/src)
file(GLOB SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/../lib/src/*.cpp)
file(GLOB HDR_FILES ${CMAKE_CURRENT_LIST_DIR}/../lib/src/*.h)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/test_runner.cpp
    ${TEST_OTHER}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
    ${SRC_FILES}
    ${HRD_FILES}
)

#find_package(qosis CONFIG REQUIRED 1.0.0.0)
#target_link_libraries(${PROJECT_NAME} qosis)
target_link_libraries(${PROJECT_NAME}
    Qt${QT_DEFAULT_MAJOR_VERSION}::Core
    Qt${QT_DEFAULT_MAJOR_VERSION}::Xml
    Qt${QT_DEFAULT_MAJOR_VERSION}::Test
)
if(${QT_DEFAULT_MAJOR_VERSION} STREQUAL "6")
    target_link_libraries(${PROJECT_NAME}
        Qt6::Core5Compat
    )
else()
    target_link_libraries(${PROJECT_NAME}
        Qt5::XmlPatterns
    )
endif()

# Uncomment this once we can detect whether package is found and if not, use relative paths instead.

#find_package(qosis CONFIG REQUIRED 0.0.0.1)

#if(APPLE)
#        find_package(Qt5 REQUIRED MacExtras)
#        target_link_libraries(${PROJECT_NAME} Qt5::MacExtras)
#elseif(MSVC)
#        find_package(Qt5 HINTS "$ENV{QT5_DIR}" COMPONENTS Core Quick REQUIRED)
#        set(CMAKE_PREFIX_PATH "C:\\Qt\\5.3.1\\5.3\\msvc2013_opengl")
#        set(Qt5_DIR "C:/Qt/Qt5.3.2/5.3/msvc2013_64_opengl/")
#        find_package(Qt5 COMPONENTS WinExtras REQUIRED)
#        target_link_libraries(${PROJECT_NAME} Qt5::WinExtras)
#endif()
