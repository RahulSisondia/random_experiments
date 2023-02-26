ADD_SUBDIRECTORY(reader_writer)

PROJECT( thread_test )
SET( THD_TEST_SOURCES
thread_test.cc)
ADD_EXECUTABLE( thread_test ${THD_TEST_SOURCES} )

PROJECT( async_pool )
SET( ASYNC_POOL_SOURCES
async_thred_pool.cc)
ADD_EXECUTABLE( async_thread_pool ${ASYNC_POOL_SOURCES} )
