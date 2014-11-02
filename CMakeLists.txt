#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.0)
#Name your project here
project(Deimos CXX)

set(DEIMOS_HEADER_DIR ${CMAKE_SOURCE_DIR}/include/Deimos)
set(DEIMOS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Core)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

file(GLOB DEIMOS_SOURCES "${DEIMOS_SOURCE_DIR}/*.cpp") # take all .cpp files
file(GLOB DEIMOS_INCLUDES "${DEIMOS_HEADER_DIR}/*.hpp") # take all .hpp files

include_directories(${DEIMOS_HEADER_DIR})

add_library(deimos SHARED ${DEIMOS_SOURCES})

