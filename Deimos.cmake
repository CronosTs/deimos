#Specify the version being used aswell as the language
cmake_minimum_required( VERSION 3.0 )
#Name your project here
project( Deimos CXX )

# PROJECT_SOURCE_DIR is the dir of this file
# CMAKE_SOURCE_DIR is the dir of root cmakelist

set( PROJECT_TARGET "${PROJECT_NAME}" )

set( INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/Deimos )
set( SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Core )
set( RUNTIME_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib )
set( ARCHIVE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIR} ) # dll and exe

# phobos3d variables
set( PHOBOS_DIR "" CACHE PATH "Path to phobos3d directory." )
set( PHOBOS_INCLUDE_DIR ${PHOBOS_DIR}/include )
set( PHOBOS_LIB_DIR ${PHOBOS_DIR}/lib )
set( PHOBOS_BIN_DIR ${PHOBOS_DIR}/bin )

# phobos3d deps
set( PHOBOS_DEPS_DIR "" CACHE PATH "Path to phobos3d dependencies directory." )
set( PHOBOS_DEPS_LIB_DIR ${PHOBOS_DEPS_DIR}/lib )
set( PHOBOS_DEPS_BIN_DIR ${PHOBOS_DEPS_DIR}/bin )
set( PHOBOS_DEPS_INCLUDE ${PHOBOS_DEPS_DIR}/SDL-1.2.15/include )

# deimos deps
set( DEIMOS_DEPS_DIR "" CACHE PATH "Path to deimos dependencies directory" )
set( DEIMOS_DEPS_LIB_DIR ${DEIMOS_DEPS_DIR}/lib)
set( DEIMOS_DEPS_BIN_DIR ${DEIMOS_DEPS_DIR}/bin)
set( DEIMOS_DEPS_INCLUDE ${DEIMOS_DEPS_DIR}/glew-1.10.0/include
                         ${DEIMOS_DEPS_DIR}/SDL_image-1.2.12 )

# boost
set( BOOST_DIR "" CACHE PATH "Path to boost dir libraries" )
set( BOOST_LIB_DIR ${BOOST_DIR}/stage/lib )

if ( PHOBOS_DIR STREQUAL "" )
    message( FATAL_ERROR "Phobos dir was not correctly configured!" )
endif()

if ( PHOBOS_DEPS_DIR STREQUAL "" )
    message( FATAL_ERROR "Phobos dependencies dir was not correctly configured!" )
endif()

if ( DEIMOS_DEPS_DIR STREQUAL "" )
    message( FATAL_ERROR "Deimos dependencies dir was not correctly configured!" )
endif()

if ( BOOST_DIR STREQUAL "" )
    message( FATAL_ERROR "Boost dir was not correctly configured!" )
endif()

# definitions
set( ALL_CONFIG_DEFS GLEW_STATIC PH_BASE_EXPORTS )
set( DEBUG_CONFIG_DEFS ${ALL_CONFIG_DEFS} PH_CHECK_ASSERT )
set( RELEASE_CONFIG_DEFS ${ALL_CONFIG_DEFS} PH_IGNORE_ASSERT )

# libraries
set( ALL_CONFIG_LIBS opengl32 glu32 )
set( DEBUG_CONFIG_LIBS ${ALL_CONFIG_LIBS}
    # phboos libs
    PH_Base_d PH_Register_d PH_System_d PH_Engine_d
    
    # phobos deps
    SDL_d SDLmain_d
    
    # deimos deps
    glew_d SDL_Image_d
)
set( RELEASE_CONFIG_LIBS ${ALL_CONFIG_LIBS}
    # phboos libs
    PH_Base PH_Register PH_System PH_Engine
    
    # phobos deps
    SDL SDLmain
    
    # deimos deps
    glew SDL_Image
)

if(MSVC)
    
    #project libs
    set( PROJECT_LIBS $<$<CONFIG:Debug>: ${DEBUG_CONFIG_LIBS}>
                      $<$<CONFIG:Release>: ${RELEASE_CONFIG_LIBS}> )
                      
    # define some macros/constants
    set( PROJECT_DEFINITIONS $<$<CONFIG:Debug>: ${DEBUG_CONFIG_DEFS}>
                             $<$<CONFIG:Release>: ${RELEASE_CONFIG_DEFS}> )
                           
    
    # get from: http://stackoverflow.com/questions/7747857/in-cmake-how-do-i-work-around-the-debug-and-release-directories-visual-studio-2
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${RUNTIME_OUTPUT_DIR} )
        set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBRARY_OUTPUT_DIR} )
        set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${ARCHIVE_OUTPUT_DIR} )
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
    
else()
    
     #project libs
    set( PROJECT_LIBS debug ${DEBUG_CONFIG_LIBS}
                      optimized ${RELEASE_CONFIG_LIBS} )
                      
    # define some macros/constants
    set( PROJECT_DEFINITIONS debug ${DEBUG_CONFIG_DEFS}
                             optimized ${RELEASE_CONFIG_DEFS} )
endif()

# add the _d on the and of binary :p
set( CMAKE_DEBUG_POSTFIX "_d" )

file( GLOB PROJECT_SOURCES "${SOURCE_DIR}/*.cpp" ) # get all .cpp files
file( GLOB PROJECT_INCLUDES "${INCLUDE_DIR}/*.hpp" ) # get all .hpp files

include_directories ( 
    ${INCLUDE_DIR}
    ${PHOBOS_INCLUDE_DIR}
    ${DEIMOS_DEPS_INCLUDE}
    ${PHOBOS_DEPS_INCLUDE}
    ${BOOST_DIR}
)

link_directories( ${PHOBOS_LIB_DIR} )
link_directories( ${PHOBOS_DEPS_LIB_DIR} )
link_directories( ${DEIMOS_DEPS_LIB_DIR} )
link_directories( ${BOOST_LIB_DIR} )

add_library( ${PROJECT_TARGET} SHARED ${PROJECT_SOURCES} ${PROJECT_INCLUDES} )

target_compile_definitions( ${PROJECT_TARGET} PRIVATE ${PROJECT_DEFINITIONS} )
target_link_libraries( ${PROJECT_TARGET}
                       ${PROJECT_LIBS} )
