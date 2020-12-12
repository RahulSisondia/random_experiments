PROJECT( tree )
SET( tree_SOURCES
main.cpp)
ADD_EXECUTABLE( tree ${tree_SOURCES} )

PROJECT( tree_util )
SET( tree_util_SOURCES
tree_util.cpp)
ADD_EXECUTABLE( tree_util ${tree_util_SOURCES} )