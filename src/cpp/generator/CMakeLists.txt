set(LIBNAME "MyriadGenerator")

set(BASE_SRCS src/AbstractGeneratorSubsystem.cpp src/GeneratorSubsystem.cpp)

set(
    BASE_HEADERS
    include/myriad/generator/AbstractGeneratorSubsystem.h
    include/myriad/generator/AbstractSequenceGenerator.h
    include/myriad/generator/GeneratorPool.h
    include/myriad/generator/GeneratorSubsystem.h
    include/myriad/generator/InvalidRecordException.h
    include/myriad/generator/RandomSequenceGenerator.h
    include/myriad/generator/StageTask.h
)

add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})