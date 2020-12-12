PROJECT( edit_distance )
SET( edit_distance_SOURCES 
EPI_17_2_edit_distance.cpp)
ADD_EXECUTABLE( edit_distance ${edit_distance_SOURCES} )

PROJECT( knapsack )
SET( knapsack_SOURCES 
knapsack.cpp
)
ADD_EXECUTABLE(knapsack ${knapsack_SOURCES} )

PROJECT( lcs )
SET( lcs_SOURCES 
longest_common_subsequence.cpp
)
ADD_EXECUTABLE(lcs ${lcs_SOURCES} )

PROJECT( mcm )
SET( mcm_SOURCES 
matrix_chain_multiplication.cpp
)
ADD_EXECUTABLE(mcm ${mcm_SOURCES} )

PROJECT( lis )
SET( lis_SOURCES 
lis.cpp
)
ADD_EXECUTABLE(lis ${lis_SOURCES} )


PROJECT( dp_misc )
SET( misc_SOURCES 
misc_main.cpp
)
ADD_EXECUTABLE(dp_misc ${misc_SOURCES} )