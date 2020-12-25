# Copyright 2020 Saroj Kumar.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(PeregrineCPPLogger)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Target OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Target CPU: ${CMAKE_SYSTEM_PROCESSOR}")

set(PGIncludeDir "${CMAKE_CURRENT_LIST_DIR}/include")
set(PGLibraryDir "${CMAKE_CURRENT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp" "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp")

file(MAKE_DIRECTORY "${PGIncludeDir}/Peregrine/Logger/")
file(COPY ${HEADER_FILES} DESTINATION "${PGIncludeDir}/Peregrine/Logger/")

add_library(PeregrineCPPLogger ${SRC_FILES})

set_target_properties(PeregrineCPPLogger PROPERTIES
    VERSION 1.0.0
    ARCHIVE_OUTPUT_DIRECTORY ${PGLibraryDir}
    LIBRARY_OUTPUT_DIRECTORY ${PGLibraryDir}
)

target_include_directories(PeregrineCPPLogger PUBLIC "${CMAKE_CURRENT_LIST_DIR}/src/")

install(
    TARGETS PeregrineCPPLogger EXPORT PeregrineCPPLoggerTargets
    ARCHIVE DESTINATION ${PGLibraryDir}
    LIBRARY DESTINATION ${PGLibraryDir}
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/PeregrineCPPLoggerConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

export(
    EXPORT PeregrineCPPLoggerTargets
    NAMESPACE PeregrineCPPLogger::
    FILE "${CMAKE_CURRENT_LIST_DIR}/cmake/PeregrineCPPLoggerTargets.cmake"
)

if (${PG_CPP_LOGGER_BUILD_EXAMPLE})
    message(STATUS "Build example: ON")

    add_executable(Example "example/main.cpp")

    set_target_properties(Example PROPERTIES
        VERSION 1.0.0
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/example/"
    )

    target_include_directories(Example PUBLIC "${PGIncludeDir}")
    target_link_directories(Example PUBLIC "${PGLibraryDir}")
    target_link_libraries(Example PUBLIC PeregrineCPPLogger)
else()
    message(STATUS "Build example: OFF")
endif()

if (${PG_CPP_LOGGER_BUILD_DOCS})
    message(STATUS "Build docs: ON")

    add_custom_target(
      docs ALL
      COMMAND "doxygen"
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
      COMMENT "Generating API documentation with Doxygen"
    )

else()
    message(STATUS "Build docs: OFF")
endif()


unset(PGIncludeDir)
unset(PGLibraryDir)
