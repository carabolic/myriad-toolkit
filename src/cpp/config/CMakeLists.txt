set(LIBNAME "MyriadConfig")

set(BASE_SRCS src/AbstractGeneratorConfig.cpp)

set(
    BASE_HEADERS
    include/myriad/config/AbstractGeneratorConfig.h
    include/myriad/config/GeneratorConfig.h
    include/myriad/config/EnumSetPool.h
    include/myriad/config/FunctionPool.h
    include/myriad/config/ObjectBuilder.h
)

add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})