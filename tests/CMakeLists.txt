cmake_minimum_required(VERSION 3.10)

if (APPLE)
    set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "CMake C Compiler")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "CMake C++ Compiler")
endif()

project(qosis-tests
        VERSION 0.0.1.2
        LANGUAGES C CXX
        DESCRIPTION "Tests for ensuring quality of the osis format library"
)

include(GNUInstallDirs)


find_package(Qt5 REQUIRED
    Core
    Xml
    XmlPatterns
    Test
)

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
)

list(APPEND TEST_OTHER
    ${CMAKE_CURRENT_LIST_DIR}/qosis-testfile.xml
    ${CMAKE_CURRENT_LIST_DIR}/qosis-files.qrc
)


add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/test_runner.cpp
    ${TEST_OTHER}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Xml Qt5::XmlPatterns Qt5::Test)
include_directories(BEFORE ${CMAKE_CURRENT_LIST_DIR}/../lib/src)
target_link_libraries(${PROJECT_NAME} qosis)

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
