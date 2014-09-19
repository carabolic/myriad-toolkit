set(LIBNAME "MyriadCore")

set(BASE_SRCS src/types/MyriadEnumSet.cpp src/exceptions.cpp src/Frontend.cpp)

set(
    BASE_HEADERS
    include/myriad/core/constants.h
    include/myriad/core/exceptions.h
    include/myriad/core/Frontend.h
    include/myriad/core/types/MyriadDate.h
    include/myriad/core/types/MyriadEnumSet.h
    include/myriad/core/types.h
)

add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})