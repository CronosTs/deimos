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

file( GLOB PROJECT_SOURCES "${SOURCE_DIR}/*.cpp" )
file( GLOB PROJECT_INCLUDES "${SOURCE_DIR}/*.hpp" )

if ( MSVC )
    set( PROJECT_DEFINITIONS $<$<CONFIG:Debug>:PH_CHECK_ASSERT PH_SDL>
                             $<$<CONFIG:Release>:PH_IGNORE_ASSERT PH_SDL> )
else()
    set( PROJECT_DEFINITIONS debug PH_CHECK_ASSERT PH_SDL
                             optimized PH_IGNORE_ASSERT PH_SDL )
endif()

include_directories( ${INCLUDE_DIR} )


add_executable ( ${PROJECT_TARGET} 
                    ${PROJECT_SOURCES}
                    ${PROJECT_INCLUDES} )

target_compile_definitions( ${PROJECT_TARGET} PRIVATE ${PROJECT_DEFINITIONS} )
target_link_libraries( ${PROJECT_TARGET} Deimos )
