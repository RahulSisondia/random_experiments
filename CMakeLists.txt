############################# Misc Problems #############################
PROJECT( test )
SET( TEST_SOURCES test/test.cpp )
ADD_EXECUTABLE( test ${TEST_SOURCES} )

############################# Array Problems #############################
PROJECT( dutch_national_flag )
SET( DUTCH_SOURCES 
arrays/dutch_national_flag.cpp)
ADD_EXECUTABLE( dutch_national_flag ${DUTCH_SOURCES} )

PROJECT( subarray_with_given_sum )
SET( SUBARRAY_SOURCES 
arrays/subarray-with-given-sum.cpp)
ADD_EXECUTABLE( subarray_with_given_sum ${SUBARRAY_SOURCES} )


############################# Graph Problems #############################
PROJECT( FindIsland )
SET( TEST_SOURCES graph/FindIsland.cpp )
ADD_EXECUTABLE( FindIsland ${TEST_SOURCES} )

############################# Tree Problems #############################
PROJECT( tree )
SET( TREE_SOURCES
tree/min_path_sum_root_to_leaf.h
tree/tree_util.h
tree/main.cpp)
ADD_EXECUTABLE( tree ${TREE_SOURCES} )

# It is important to set the debug flag (-g) to debug the binaries in  VScode.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++17 -g")
