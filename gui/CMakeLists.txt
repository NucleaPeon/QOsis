cmake_minimum_required(VERSION 3.10)
project(qosis-cli
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Graphical User Interface"
)

include(GNUInstallDirs)  # REQUIRED TO INSTALL PKGCONFIG TO PROPER DIR!
include(CTest)

message(STATUS "Building OSIS GUI...")

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h @ONLY)
