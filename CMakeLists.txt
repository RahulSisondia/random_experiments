############## Settings for all projects ################################
cmake_minimum_required(VERSION 3.16)
# Do the debug build only
SET(CMAKE_BUILD_TYPE Debug)
# Set the  cpp standard to  C++17
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

############################# Misc Problems #############################
PROJECT( test )
SET( TEST_SOURCES test/test.cpp )
ADD_EXECUTABLE( test ${TEST_SOURCES} )
##########################################################################

############################# Bits Problems #############################
ADD_SUBDIRECTORY(bits)
##########################################################################

############################# Array Problems #############################
ADD_SUBDIRECTORY(arrays)
##############################################################################

############################# Graph Problems #############################
ADD_SUBDIRECTORY(graph)
##############################################################################

############################# Tree Problems #############################
ADD_SUBDIRECTORY(tree)
##############################################################################

############################# Hasing  Problems #############################
ADD_SUBDIRECTORY(hashing)
############################################################################

############################# Sorting  Problems #############################
ADD_SUBDIRECTORY(Sorting)
############################################################################

############################# Threading  Problems #############################
ADD_SUBDIRECTORY(threads)
##############################################################################

############################# CPP  Problems #############################
ADD_SUBDIRECTORY(cpp)
##############################################################################

############################# Leetcode  Problems #############################
ADD_SUBDIRECTORY(leetcode)
##############################################################################
