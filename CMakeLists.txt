cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

if(NOT ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()

project(PeregrineCPPLogger)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB SRC_FILES "src/*.hpp" "src/*.cpp")

add_library(PeregrineCPPLogger ${SRC_FILES})
target_include_directories(PeregrineCPPLogger PUBLIC "src/")
