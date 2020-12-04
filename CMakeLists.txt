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

if(NOT ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()

project(PeregrineCPPLogger)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB SRC_FILES "src/*.hpp" "src/*.cpp")

add_library(PeregrineCPPLogger ${SRC_FILES})
target_include_directories(PeregrineCPPLogger PUBLIC "src/")
