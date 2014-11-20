cmake_minimum_required( VERSION 3.0 )

project ( Sample_01 CXX )

set( PROJECT_TARGET "${PROJECT_NAME}" )

set( SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Sample_01 )
set( INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include )

set( RUNTIME_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib )
set( ARCHIVE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/lib )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIR} ) # dll and exe

set( PHOBOS_DIR "" CACHE PATH "Path to phobos3d directory." )
set( PHOBOS_LIB_DIR ${PHOBOS_DIR}/lib )

set( DEIMOS_DEPS_DIR "" CACHE PATH "Path to deimos dependencies directory." )
set( DEIMOS_LIB_DIR ${DEIMOS_DEPS_DIR}/lib )

set( PHOBOS_DEPS_DIR "" CACHE PATH "Path to phobos dependencies directory." )
set( PHOBOS_DEPS_LIB_DIR ${PHOBOS_DEPS_DIR}/lib )

file( GLOB PROJECT_SOURCES "${SOURCE_DIR}/*.cpp" )
file( GLOB PROJECT_INCLUDES "${SOURCE_DIR}/*.hpp" )

set( ALL_CONFIG_LIB "" )
set( DEBUG_CONFIG_LIB ${ALL_CONFIG_LIB} PH_Base_d PH_Register_d PH_System_d )
set( RELEASE_CONFIG_LIB ${ALL_CONFIG_LIB} PH_Base PH_Register PH_System )

if ( MSVC )
    set( PROJECT_DEFINITIONS $<$<CONFIG:Debug>:PH_CHECK_ASSERT PH_SDL>
                             $<$<CONFIG:Release>:PH_IGNORE_ASSERT PH_SDL> )
    set( PROJECT_LIBS $<$<CONFIG:Debug>: ${DEBUG_CONFIG_LIB}> 
                      $<$<CONFIG:Release>: ${RELEASE_CONFIG_LIB}> )
                      
    # get from: http://stackoverflow.com/questions/7747857/in-cmake-how-do-i-work-around-the-debug-and-release-directories-visual-studio-2
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${RUNTIME_OUTPUT_DIR} )
        set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBRARY_OUTPUT_DIR} )
        set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${ARCHIVE_OUTPUT_DIR} )
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
    
else()
    set( PROJECT_DEFINITIONS debug PH_CHECK_ASSERT PH_SDL
                             optimized PH_IGNORE_ASSERT PH_SDL )
    set( PROJECT_LIBS debug ${DEBUG_CONFIG_LIB}
                      optimized ${RELEASE_CONFIG_LIB} )
endif()

include_directories( ${INCLUDE_DIR} )

link_directories( ${PHOBOS_LIB_DIR} 
                  ${DEIMOS_LIB_DIR}
                  ${PHOBOS_DEPS_LIB_DIR} )

add_executable ( ${PROJECT_TARGET} 
                    ${PROJECT_SOURCES}
                    ${PROJECT_INCLUDES} )

target_compile_definitions( ${PROJECT_TARGET} PRIVATE ${PROJECT_DEFINITIONS} )
target_link_libraries( ${PROJECT_TARGET}
                        ${PROJECT_LIBS} 
                        Deimos )
