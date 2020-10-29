############## Settings for all projects ################################
cmake_minimum_required(VERSION 3.16)
# Do the debug build only
SET(CMAKE_BUILD_TYPE Debug)
# Set the  cpp standard to  C++17

add_compile_options(-std=c++17 -g -Wall)
# Enable address Sanitizer. Note it is important to set the flags to compiler and linker both. 
# https://clang.llvm.org/docs/AddressSanitizer.html#how-to-build
add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
string(APPEND CMAKE_EXE_LINKER_FLAGS "-fsanitize=address")
# Set undefined behavior sanitizers 
# https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
add_compile_options(-fsanitize=undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds,nullability )
add_compile_options(-fno-sanitize-recover=null -fsanitize-trap=alignment -fno-omit-frame-pointer)

# Generate the output binaries at one place in the bin directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

############################ Misc Problems #############################
PROJECT( test )
SET( TEST_SOURCES test/test.cpp )
ADD_EXECUTABLE( test ${TEST_SOURCES} )
#########################################################################

############################# Bits Problems #############################
ADD_SUBDIRECTORY(bits)
##########################################################################

################################# Array Problems #############################
ADD_SUBDIRECTORY(arrays)
##############################################################################

################################# Linklist Problems #########################
ADD_SUBDIRECTORY(linklist)
##############################################################################

################################# Graph Problems #############################
ADD_SUBDIRECTORY(graph)
##############################################################################

################################## Tree Problems #############################
ADD_SUBDIRECTORY(tree)
##############################################################################

############################# Hasing  Problems #############################
ADD_SUBDIRECTORY(hashing)
############################################################################

############################# Sorting  Problems #############################
ADD_SUBDIRECTORY(sorting)
#############################################################################

############################# Searching  Problems #############################
ADD_SUBDIRECTORY(searching)
#############################################################################

############################# Backtracking  Problems ########################
ADD_SUBDIRECTORY(backtracking)
#############################################################################

############################# Recursion  Problems ########################
ADD_SUBDIRECTORY(recursion)
#############################################################################

####################### Dynamic Programing  Problems ########################
ADD_SUBDIRECTORY(dp)
#############################################################################

############################# Threading  Problems #############################
ADD_SUBDIRECTORY(threads)
###############################################################################

################################## CPP  Problems #############################
ADD_SUBDIRECTORY(cpp)
##############################################################################

############################# Leetcode  Problems #############################
ADD_SUBDIRECTORY(leetcode)
##############################################################################

############################# Interviewbit  Problems #########################
ADD_SUBDIRECTORY(ib)
##############################################################################

############################# Dailybyte  Problems #########################
ADD_SUBDIRECTORY(daily_byte)
##############################################################################