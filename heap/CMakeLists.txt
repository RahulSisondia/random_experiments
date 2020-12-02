SET( std_heap_check_SOURCES
std_heap_check.cpp
)
ADD_EXECUTABLE( heap_check ${std_heap_check_SOURCES} )

SET (heap_SOURCES
main.cpp
) 
ADD_EXECUTABLE(heap ${heap_SOURCES})