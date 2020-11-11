PROJECT( tree )
SET( tree_SOURCES
main.cpp)
ADD_EXECUTABLE( tree ${tree_SOURCES} )

PROJECT( tree_util )
SET( tree_util_SOURCES
tree_util.cpp)
ADD_EXECUTABLE( tree_util ${tree_util_SOURCES} )

PROJECT (inorder_successor)
SET( inorder_successor_SOURCES
inorder_successor.cpp) 
ADD_EXECUTABLE( inorder_successor ${inorder_successor_SOURCES} )