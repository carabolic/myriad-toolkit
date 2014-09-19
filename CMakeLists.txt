cmake_minimum_required(VERSION 2.6)
project(myriad-toolkit)

set(MYRIAD_VERSION 0.3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

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

# find and include third party libraries
find_package(Poco COMPONENTS Foundation Net Util XML REQUIRED)

message(${Poco_INCLUDE_DIRS})
include_directories(${Poco_INCLUDE_DIRS})

include_directories(
    src/cpp/communication/include
    src/cpp/config/include
    src/cpp/core/include
    src/cpp/generator/include
    src/cpp/io/include
    src/cpp/math/include
    src/cpp/record/include
    src/cpp/runtime/include
)

add_subdirectory(src/cpp/communication)
add_subdirectory(src/cpp/config)
add_subdirectory(src/cpp/core)
add_subdirectory(src/cpp/generator)
add_subdirectory(src/cpp/io)
add_subdirectory(src/cpp/math)
add_subdirectory(src/cpp/record)
add_subdirectory(src/cpp/runtime)

add_executable(myriad Main.cpp XmlHandler.cpp XmlHandler.h) # TODO add myriad add_executable
target_link_libraries(
    myriad
    MyriadCommunication
    MyriadConfig
    MyriadCore
    MyriadGenerator
#    MyriadIO
    MyriadMath
#    MyriadRecord
#    MyriadRuntime
    ${Poco_LIBRARIES}
) # TODO link myriad executable against myriad runtime
