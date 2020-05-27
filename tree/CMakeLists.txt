PROJECT( tree )
SET( TREE_SOURCES
min_path_sum_root_to_leaf.h
tree_util.h
main.cpp)

ADD_EXECUTABLE( tree ${TREE_SOURCES} )

PROJECT (inorder_successor)
SET( inorder_successor_SOURCES
inorder_successor.cpp
) 
ADD_EXECUTABLE( inorder_successor ${inorder_successor_SOURCES} )