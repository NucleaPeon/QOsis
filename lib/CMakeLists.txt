cmake_minimum_required(VERSION 3.10)
project(qosis
        VERSION 0.0.1.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Library"
)

message(STATUS "Building OSIS Library...")
message(STATUS "${CMAKE_C_COMPILER} C Compiler")
message(STATUS "${CMAKE_CXX_COMPILER} C++ Compiler")

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_LIST_DIR}/version.h.in
    ${CMAKE_CURRENT_LIST_DIR}/src/version.h @ONLY)


find_package(Qt5 REQUIRED
    Core
    Xml
)

set(PACKAGE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/qosis.h
)

list(APPEND QOSIS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/qosis.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisreader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosiswriter.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisvalidator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisimporter.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisexporter.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosiscommons.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosismeta.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosis_global.h
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisglobals.h
    ${CMAKE_CURRENT_LIST_DIR}/src/version.h
)


list(APPEND QOSIS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/qosis.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosiscommons.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisreader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosiswriter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisvalidator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisimporter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosisexporter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qosismeta.cpp
)

add_library(${PROJECT_NAME}
        SHARED
        ${QOSIS_HEADERS}
        ${QOSIS_SOURCES}
)

target_link_libraries(${PROJECT_NAME} Qt5::Xml)
target_include_directories(${PROJECT_NAME} PUBLIC src/)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
    SOVERSION 2
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${QOSIS_HEADERS}")
configure_file(${CMAKE_CURRENT_LIST_DIR}/src/qosis.pc.in ${CMAKE_CURRENT_LIST_DIR}/src/qosis.pc @ONLY)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
file(MAKE_DIRECTORY ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    CACHE PATH "Location of header files" )
set(SYSCONFIG_INSTALL_DIR ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME}
    CACHE PATH "Location of configuration files" )

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-config.cmake.in
  ${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)
write_basic_package_version_file(
  ${CMAKE_CURRENT_LIST_DIR}-config-version.cmake
  VERSION ${VERSION}
  COMPATIBILITY SameMajorVersion )
#configure_file(${CMAKE_CURRENT_LIST_DIR}/qosis.pc.in ${CMAKE_CURRENT_LIST_DIR}/qosis.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME} )
install(FILES ${CMAKE_CURRENT_LIST_DIR}/src/qosis.pc DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


