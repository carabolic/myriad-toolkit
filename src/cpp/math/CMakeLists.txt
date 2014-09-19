set(LIBNAME "MyriadMath")

set(BASE_SRCS src/algebra/MultiplicativeGroup.cpp src/probability/Probability.cpp src/random/RNG.cpp)

set(
    BASE_HEADERS
    include/myriad/math/algebra/MultiplicativeGroup.h
    include/myriad/math/Function.h
    include/myriad/math/Interval.h
    include/myriad/math/probability/BoundedNormalPrFunction.h
    include/myriad/math/probability/BoundedParetoPrFunction.h
    include/myriad/math/probability/CombinedPrFunction.h
    include/myriad/math/probability/ConditionalCombinedPrFunction.h
    include/myriad/math/probability/NormalPrFunction.h
    include/myriad/math/probability/ParetoPrFunction.h
    include/myriad/math/probability/Probability.h
    include/myriad/math/probability/UniformPrFunction.h
    include/myriad/math/random/CompoundEICG.h
    include/myriad/math/random/EICG.h
    include/myriad/math/random/HashRandomStream.h
    include/myriad/math/random/NativeRandomStream.h
    include/myriad/math/random/RandomSeed.h
    include/myriad/math/random/RandomStream.h
    include/myriad/math/random/RNG.h
    include/myriad/math/util.h
)

add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})