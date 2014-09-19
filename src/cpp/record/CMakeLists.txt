set(LIBNAME "MyriadRecord")

set(BASE_SRCS )

set(
    BASE_HEADERS
    include/myriad/record/AbstractRecord.h
)

# add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})
# workaround to build header only library
add_custom_target(${LIBNAME} SOURCES ${BASE_HEADERS})