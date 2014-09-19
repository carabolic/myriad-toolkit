set(LIBNAME "MyriadIO")

set(BASE_SRCS )

set(
    BASE_HEADERS
    include/myriad/io/AbstractOutputCollector.h
    include/myriad/io/LocalFileOutputCollector.h
    include/myriad/io/OutputCollector.h
    include/myriad/io/SocketStreamOutputCollector.h
    include/myriad/io/VoidOutputCollector.h
)

# add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})
# workaround to build header only library
add_custom_target(${LIBNAME} SOURCES ${BASE_HEADERS})