cmake_minimum_required(VERSION 3.10)

if (APPLE)
    set(CMAKE_C_COMPILER /usr/bin/clang CACHE PATH "CMake C Compiler")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++ CACHE PATH "CMake C++ Compiler")
endif()

project(qosis-tests
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "Tests for ensuring quality of the osis format library"
)

include(GNUInstallDirs)

list(APPEND TEST_SOURCES

)

list(APPEND TEST_HEADERS

)

list(APPEND TEST_OTHER

)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/test_runner.cpp
    ${TEST_OTHER}
    ${TEST_HEADERS}
    ${TEST_SOURCES}
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Xml Qt5::Test)

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
