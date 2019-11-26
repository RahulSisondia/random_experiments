PROJECT( reader_writer )
SET( RW_SOURCES
read_write_lock.h
reader_writer.h
semaphore.h
main.cpp)
ADD_EXECUTABLE( reader_writer ${RW_SOURCES} )
