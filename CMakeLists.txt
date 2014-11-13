#Specify the version being used aswell as the language
cmake_minimum_required( VERSION 3.0 )
#Name your project here
project( AllProjects CXX )

option( WITH_SAMPLES "Add samples cmake files." OFF)

if ( WITH_SAMPLES )
    include( Sample_01.cmake )
endif( WITH_SAMPLES )

include( Deimos.cmake ) # the last cmake file is that will name the visual studio solution