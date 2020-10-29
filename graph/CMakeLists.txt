PROJECT( graph_primer )
SET( graph_primer_SOURCES graph_primer.cpp )
ADD_EXECUTABLE( graph_primer ${graph_primer_SOURCES} )

PROJECT( dfs_bfs )
SET( dfs_bfs_SOURCES dfs_bfs_findisland.cpp )
ADD_EXECUTABLE( dfs_bfs_findisland ${dfs_bfs_SOURCES} )


PROJECT( min_spanning_tree )
SET( MIN_SPANNING_SOURCES Min_Spanning_Tree.cpp )
ADD_EXECUTABLE( min_spanning_tree ${MIN_SPANNING_SOURCES} )

