set(LIBNAME "MyriadRuntime")

set(BASE_SRCS )

set(
    BASE_HEADERS
    include/myriad/runtime/predicate/EqualityPredicate.h
    include/myriad/runtime/provider/predicate/AbstractFieldBinder.h
    include/myriad/runtime/provider/predicate/EqualityPredicateFieldBinder.h
    include/myriad/runtime/provider/predicate/EqualityPredicateProvider.h
    include/myriad/runtime/provider/range/AbstractRangeProvider.h
    include/myriad/runtime/provider/range/ConstRangeProvider.h
    include/myriad/runtime/provider/range/ContextFieldRangeProvider.h
    include/myriad/runtime/provider/reference/AbstractReferenceProvider.h
    include/myriad/runtime/provider/reference/ClusteredReferenceProvider.h
    include/myriad/runtime/provider/reference/RandomReferenceProvider.h
    include/myriad/runtime/provider/value/AbstractValueProvider.h
    include/myriad/runtime/provider/value/AggregateChildFieldValueProvider.h
    include/myriad/runtime/provider/value/CallbackValueProvider.h
    include/myriad/runtime/provider/value/ClusteredValueProvider.h
    include/myriad/runtime/provider/value/ConstValueProvider.h
    include/myriad/runtime/provider/value/ContextFieldValueProvider.h
    include/myriad/runtime/provider/value/ElementWiseValueProvider.h
    include/myriad/runtime/provider/value/RandomValueProvider.h
    include/myriad/runtime/setter/AbstractSetter.h
    include/myriad/runtime/setter/FieldSetter.h
    include/myriad/runtime/setter/ReferenceSetter.h
    include/myriad/runtime/setter/SetterChain.h
)

# add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})
# workaround to build header only library
add_custom_target(${LIBNAME} SOURCES ${BASE_HEADERS})