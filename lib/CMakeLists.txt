cmake_minimum_required(VERSION 3.10)
project(libqosis
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Library"
)

message(STATUS "Building OSIS Library...")
message(STATUS "${CMAKE_C_COMPILER} C Compiler")
message(STATUS "${CMAKE_CXX_COMPILER} C++ Compiler")

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_LIST_DIR}/version.h.in
    ${CMAKE_CURRENT_LIST_DIR}/version.h @ONLY)
