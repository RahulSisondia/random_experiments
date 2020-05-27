PROJECT( merge_sort )
SET( M_SORT_SOURCES 
merge_sort.cpp )

ADD_EXECUTABLE( merge_sort ${M_SORT_SOURCES} )

PROJECT(quick_sort)
SET (Q_SORT_SOURCES quick_sort.cpp)
ADD_EXECUTABLE(quick_sort ${Q_SORT_SOURCES})