cmake_minimum_required(VERSION 2.8.0)
project(DataStructure)

include_directories(include)

add_subdirectory(src)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    message(STATUS "Build for Windows")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Build for Linux")
endif()

add_subdirectory(test)