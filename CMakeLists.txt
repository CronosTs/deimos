#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.0)
#Name your project here
project(Deimos CXX)

set(DEIMOS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Deimos)
set(DEIMOS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Core)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# phobos3d variables
set(PHOBOS_DIR $ENV{PHOBOS_DIR})
set(PHOBOS_INCLUDE_DIR ${PHOBOS_DIR}/include)
set(PHOBOS_LIB_DIR ${PHOBOS_DIR}/lib)
set(PHOBOS_BIN_DIR ${PHOBOS_DIR}/bin)

file(GLOB DEIMOS_SOURCES "${DEIMOS_SOURCE_DIR}/*.cpp") # get all .cpp files
file(GLOB DEIMOS_INCLUDES "${DEIMOS_INCLUDE_DIR}/*.hpp") # get all .hpp files

include_directories(${DEIMOS_INCLUDE_DIR})
include_directories(${PHOBOS_INCLUDE_DIR})
link_directories(${PHOBOS_LIB_DIR})

add_library(deimos SHARED ${DEIMOS_SOURCES} ${DEIMOS_INCLUDES})

target_link_libraries(deimos PH_Base PH_System PH_Register)

