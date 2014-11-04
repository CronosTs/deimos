#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 3.0)
#Name your project here
project(Deimos CXX)

set(DEIMOS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Deimos)
set(DEIMOS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/Core)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # dll and exe

# phobos3d variables
set(PHOBOS_DIR "" CACHE PATH "Path to phobos3d directory.")
set(PHOBOS_INCLUDE_DIR ${PHOBOS_DIR}/include)
set(PHOBOS_LIB_DIR ${PHOBOS_DIR}/lib)
set(PHOBOS_BIN_DIR ${PHOBOS_DIR}/bin)

# phobos3d deps
set(PHOBOS_DEPS_DIR "" CACHE PATH "Path to phobos3d dependencies directory.")
set(PHOBOS_DEPS_LIB_DIR ${PHOBOS_DEPS_DIR}/lib)
set(PHOBOS_DEPS_BIN_DIR ${PHOBOS_DEPS_DIR}/bin)
set(PHOBOS_DEPS_INCLUDE ${PHOBOS_DEPS_DIR}/SDL-1.2.15/include)

# deimos deps
set(DEIMOS_DEPS_DIR "" CACHE PATH "Path to deimos dependencies directory")
set(DEIMOS_DEPS_LIB_DIR ${DEIMOS_DEPS_DIR}/lib)
set(DEIMOS_DEPS_BIN_DIR ${DEIMOS_DEPS_DIR}/bin)
set(DEIMOS_DEPS_INCLUDE ${DEIMOS_DEPS_DIR}/glew-1.10.0/include
                        ${DEIMOS_DEPS_DIR}/SDL_image-1.2.12)

# boost
set(BOOST_DIR "" CACHE PATH "Path to boost dir libraries")
set(BOOST_LIB_DIR ${BOOST_DIR}/stage/lib)

if (PHOBOS_DIR STREQUAL "")
    message(FATAL_ERROR "Phobos dir was not correctly configured!")
endif()

if (PHOBOS_DEPS_DIR STREQUAL "")
    message(FATAL_ERROR "Phobos dependencies dir was not correctly configured!")
endif()

if (DEIMOS_DEPS_DIR STREQUAL "")
    message(FATAL_ERROR "Deimos dependencies dir was not correctly configured!")
endif()

if (BOOST_DIR STREQUAL "")
    message(FATAL_ERROR "Boost dir was not correctly configured!")
endif()

if(MSVC)
    set(PHOBOS_LIBS $<$<CONFIG:Debug>:PH_Base_d PH_System_d PH_Register_d>
                    $<$<CONFIG:Release>:PH_Base PH_System PH_Register>)
                    
    set(PHOBOS_DEPS_LIBS $<$<CONFIG:Debug>:SDL_d SDLmain_d opengl32 glu32>
                         $<$<CONFIG:Release>:SDL SDLmain> opengl32 glu32)

    set(DEIMOS_DEPS_LIBS $<$<CONFIG:Debug>:glew_d SDL_Image_d>
                         $<$<CONFIG:Release>:glew SDL_Image>)
                         
     set(BOOST_LIBS $<$<CONFIG:Debug>:>
                    $<$<CONFIG:Release>:>)
    # define some macros/constants
    set(DEIMOS_DEFINITIONS $<$<CONFIG:Debug>:PH_CHECK_ASSERT  PH_SDL GLEW_STATIC PH_BASE_EXPORTS>
                           $<$<CONFIG:Release>:PH_IGNORE_ASSERT  PH_SDL GLEW_STATIC PH_BASE_EXPORTS>)
else()
    set(PHOBOS_LIBS debug PH_Base_d PH_System_d PH_Register_d
                    optimized PH_Base PH_System PH_Register)
    set(PHOBOS_DEPS_LIBS debug SDL_d SDLmain_d
                         optimized SDL SDLmain)
    set(DEIMOS_DEPS_LIBS debug glew_d SDL_Image_d
                         optimized glew SDL_Image)
    set(BOOST_LIBS debug
                   optimized)
                    
    set(DEIMOS_DEFINITIONS debug PH_CHECK_ASSERT PH_SDL GLEW_STATIC
                           optimized PH_IGNORE_ASSERT PH_SDL GLEW_STATIC)
endif()

file(GLOB DEIMOS_SOURCES "${DEIMOS_SOURCE_DIR}/*.cpp") # get all .cpp files
file(GLOB DEIMOS_INCLUDES "${DEIMOS_INCLUDE_DIR}/*.hpp") # get all .hpp files

include_directories(${DEIMOS_INCLUDE_DIR}
                    ${PHOBOS_INCLUDE_DIR}
                    ${DEIMOS_DEPS_INCLUDE}
                    ${PHOBOS_DEPS_INCLUDE}
                    ${BOOST_DIR})


link_directories(${PHOBOS_LIB_DIR})
link_directories(${PHOBOS_DEPS_LIB_DIR})
link_directories(${DEIMOS_DEPS_LIB_DIR})
link_directories(${BOOST_LIB_DIR})

add_library(deimos SHARED ${DEIMOS_SOURCES} ${DEIMOS_INCLUDES})

target_compile_definitions(deimos PRIVATE ${DEIMOS_DEFINITIONS})
target_link_libraries(deimos ${PHOBOS_LIBS}
                             ${DEIMOS_DEPS_LIBS}
                             ${PHOBOS_DEPS_LIBS}
                             ${BOOST_LIBS})
