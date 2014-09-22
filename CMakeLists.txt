cmake_minimum_required(VERSION 2.8)
project(myriad-toolkit)

set(MYRIAD_VERSION 0.4.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(MYRIAD_HEADERS src/cpp/communication/CommunicationSubsystem.h
                   src/cpp/communication/Notifications.h
                   src/cpp/config/AbstractGeneratorConfig.h
                   src/cpp/config/EnumSetPool.h
                   src/cpp/config/FunctionPool.h
                   src/cpp/config/GeneratorConfig.h
                   src/cpp/config/ObjectBuilder.h
                   src/cpp/core/constants.h
                   src/cpp/core/exceptions.h
                   src/cpp/core/Frontend.h
                   src/cpp/core/types/MyriadDate.h
                   src/cpp/core/types/MyriadEnumSet.h
                   src/cpp/core/types.h
                   src/cpp/generator/AbstractGeneratorSubsystem.h
                   src/cpp/generator/AbstractSequenceGenerator.h
                   src/cpp/generator/GeneratorPool.h
                   src/cpp/generator/GeneratorSubsystem.h
                   src/cpp/generator/InvalidRecordException.h
                   src/cpp/generator/RandomSequenceGenerator.h
                   src/cpp/generator/StageTask.h
                   src/cpp/io/AbstractOutputCollector.h
                   src/cpp/io/LocalFileOutputCollector.h
                   src/cpp/io/OutputCollector.h
                   src/cpp/io/SocketStreamOutputCollector.h
                   src/cpp/io/VoidOutputCollector.h
                   src/cpp/math/algebra/MultiplicativeGroup.h
                   src/cpp/math/Function.h
                   src/cpp/math/Interval.h
                   src/cpp/math/probability/BoundedNormalPrFunction.h
                   src/cpp/math/probability/BoundedParetoPrFunction.h
                   src/cpp/math/probability/CombinedPrFunction.h
                   src/cpp/math/probability/ConditionalCombinedPrFunction.h
                   src/cpp/math/probability/NormalPrFunction.h
                   src/cpp/math/probability/ParetoPrFunction.h
                   src/cpp/math/probability/Probability.h
                   src/cpp/math/probability/UniformPrFunction.h
                   src/cpp/math/random/CompoundEICG.h
                   src/cpp/math/random/EICG.h
                   src/cpp/math/random/HashRandomStream.h
                   src/cpp/math/random/NativeRandomStream.h
                   src/cpp/math/random/RandomSeed.h
                   src/cpp/math/random/RandomStream.h
                   src/cpp/math/random/RNG.h
                   src/cpp/math/util.h
                   src/cpp/packages.h
                   src/cpp/record/AbstractRecord.h
                   src/cpp/runtime/predicate/EqualityPredicate.h
                   src/cpp/runtime/provider/predicate/AbstractFieldBinder.h
                   src/cpp/runtime/provider/predicate/EqualityPredicateFieldBinder.h
                   src/cpp/runtime/provider/predicate/EqualityPredicateProvider.h
                   src/cpp/runtime/provider/range/AbstractRangeProvider.h
                   src/cpp/runtime/provider/range/ConstRangeProvider.h
                   src/cpp/runtime/provider/range/ContextFieldRangeProvider.h
                   src/cpp/runtime/provider/reference/AbstractReferenceProvider.h
                   src/cpp/runtime/provider/reference/ClusteredReferenceProvider.h
                   src/cpp/runtime/provider/reference/RandomReferenceProvider.h
                   src/cpp/runtime/provider/value/AbstractValueProvider.h
                   src/cpp/runtime/provider/value/AggregateChildFieldValueProvider.h
                   src/cpp/runtime/provider/value/CallbackValueProvider.h
                   src/cpp/runtime/provider/value/ClusteredValueProvider.h
                   src/cpp/runtime/provider/value/ConstValueProvider.h
                   src/cpp/runtime/provider/value/ContextFieldValueProvider.h
                   src/cpp/runtime/provider/value/ElementWiseValueProvider.h
                   src/cpp/runtime/provider/value/RandomValueProvider.h
                   src/cpp/runtime/setter/AbstractSetter.h
                   src/cpp/runtime/setter/FieldSetter.h
                   src/cpp/runtime/setter/ReferenceSetter.h
                   src/cpp/runtime/setter/SetterChain.h
)

set(MYRIAD_SOURCES src/cpp/communication/CommunicationSubsystem.cpp
                   src/cpp/config/AbstractGeneratorConfig.cpp
                   src/cpp/core/exceptions.cpp
                   src/cpp/core/Frontend.cpp
                   src/cpp/core/types/MyriadEnumSet.cpp
                   src/cpp/generator/AbstractGeneratorSubsystem.cpp
                   src/cpp/generator/GeneratorSubsystem.cpp
                   src/cpp/math/algebra/MultiplicativeGroup.cpp
                   src/cpp/math/probability/Probability.cpp
                   src/cpp/math/random/RNG.cpp
)

# create API docs with custom target
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set variables
    set(doxyfile_in ${PROJECT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${PROJECT_BINARY_DIR}/Doxfile)

    # set placeholders
    set(DOXY_INPUT ${CMAKE_SOURCE_DIR}/src/cpp)
    set(DOXY_IMAGE_DIR ${CMAKE_SOURCE_DIR}/src/resources/images/logo.png)
    set(DOXY_OUTPUT_ROOT ${CMAKE_CURRENT_BINARY_DIR}/doc)
    set(doxy_extra_files "")

    # copy Doxyfile and replace @PLACEHOLDERS@
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    # custom doc target, unfortunately without dependency tracking
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile} DEPENDS ${DOXY_INPUT})

else(DOXYGEN_FOUND)
    message(FATAL_ERROR "doxygen not found!")
endif(DOXYGEN_FOUND)

find_package(Poco COMPONENTS Foundation Net Util XML REQUIRED)

include_directories("src/cpp")
include_directories(${Poco_INCLUDE_DIRS})

add_custom_target(libMyriadToolkit SOURCES ${MYRIAD_HEADERS})


# actually build the toolkit
#
add_library(myriad-toolkit ${MYRIAD_SOURCES} ${MYRIAD_HEADERS})

target_link_libraries(
    myriad-toolkit
    ${Poco_LIBRARIES}
)

# TESTING
## set root folder for google testing framework
set(GTEST_ROOT "test/gtest")

## set the test sources
set(MYRIAD_TESTS_SOURCES test/cpp/math/probability/UniformPrFunctionTest.cpp
)

add_subdirectory(${GTEST_ROOT})

include_directories(${GTEST_ROOT}/include)

add_executable(tests ${MYRIAD_TESTS_SOURCES})

target_link_libraries(
    tests
    myriad-toolkit
    gtest_main
)
