#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.0)
#Name your project here
project(Deimos CXX)

set(DEIMOS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Deimos)
set(DEIMOS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Core)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# phobos3d variables
set(PHOBOS_DIR "" CACHE PATH "Path to phobos3d directory.")
set(PHOBOS_INCLUDE_DIR ${PHOBOS_DIR}/include)
set(PHOBOS_LIB_DIR ${PHOBOS_DIR}/lib)
set(PHOBOS_BIN_DIR ${PHOBOS_DIR}/bin)

# phobos3d deps
set(PHOBOS_DEPS_DIR "" CACHE PATH "Path to phobos3d dependencies directory.")
set(PHOBOS_DEPS_INCLUDE_DIR ${PHOBOS_DEPS_DIR}/include)
set(PHOBOS_DEPS_LIB_DIR ${PHOBOS_DEPS_DIR}/lib)
set(PHOBOS_DEPS_BIN_DIR ${PHOBOS_DEPS_DIR}/bin)

# deimos deps
set(DEIMOS_DEPS_DIR "" CACHE PATH "Path to deimos dependencies directory")
set(DEIMOS_DEPS_INCLUDE_DIR ${DEIMOS_DEPS_DIR}/include)
set(DEIMOS_DEPS_LIB_DIR ${DEIMOS_DEPS_DIR}/lib)
set(DEIMOS_DEPS_BIN_DIR ${DEIMOS_DEPS_DIR}/bin)

# boost
set(BOOST_DIR "" CACHE PATH "Path to boost dir libraries")
set(BOOST_INCLUDE_DIR ${BOOST_DIR}/include)
set(BOOST_LIB_DIR ${BOOST_DIR}/stage/lib)

if (PHOBOS_DIR STREQUAL "")
    # message(FATAL_ERROR "Phobos dir was not correctly configured!")
endif()

if (PHOBOS_DEPS_DIR STREQUAL "")
    # message(FATAL_ERROR "Phobos dependencies dir was not correctly configured!")
endif()

if(MSVC)
    set(PHOBOS_LIBS $<$<CONFIG:Debug>:PH_Base_d PH_System_d PH_Register_d>
                    $<$<CONFIG:Release>:PH_Base PH_System PH_Register>)
    # define some macros/constants
    set(DEIMOS_DEFINITIONS $<$<CONFIG:Debug>:PH_CHECK_ASSERT  PH_SDL>
                           $<$<CONFIG:Release>:PH_IGNORE_ASSERT  PH_SDL>)
else()
    set(PHOBOS_LIBS debug PH_Base_d PH_System_d PH_Register_d
                    optimized PH_Base PH_System PH_Register)
    set(DEIMOS_DEFINITIONS debug PH_CHECK_ASSERT PH_SDL
                           optimized PH_IGNORE_ASSERT PH_SDL)
endif()

file(GLOB DEIMOS_SOURCES "${DEIMOS_SOURCE_DIR}/*.cpp") # get all .cpp files
file(GLOB DEIMOS_INCLUDES "${DEIMOS_INCLUDE_DIR}/*.hpp") # get all .hpp files

include_directories(${DEIMOS_INCLUDE_DIR})
include_directories(${PHOBOS_INCLUDE_DIR})
link_directories(${PHOBOS_LIB_DIR})

add_library(deimos SHARED ${DEIMOS_SOURCES} ${DEIMOS_INCLUDES})

target_compile_definitions(deimos PRIVATE ${DEIMOS_DEFINITIONS})
target_link_libraries(deimos ${PHOBOS_LIBS})




