cmake_minimum_required(VERSION 2.6)
project(myriad-toolkit)

set(MYRIAD_VERSION 0.3.0)

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
        doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile} DEPENDS ${DOXY_INPUT})

else(DOXYGEN_FOUND)
    message(FATAL_ERROR "doxygen not found!")
endif(DOXYGEN_FOUND)
