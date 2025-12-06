cmake_minimum_required(VERSION 3.10)
project(qosis-cli
        VERSION 0.0.0.1
        LANGUAGES C CXX
        DESCRIPTION "OSIS (Open Scriptural Information Standard™) Command Line Interface"
)

message(STATUS "Building OSIS CLI...")

# Immediately set the version.h header
configure_file(${CMAKE_CURRENT_LIST_DIR}/version.h.in
    ${CMAKE_CURRENT_LIST_DIR}/version.h @ONLY)
