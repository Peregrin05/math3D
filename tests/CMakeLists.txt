cmake_minimum_required(VERSION 2.8.4)
project(tests)

enable_testing()

set (MATH_LIB flash_math)

set (${MATH_LIB}_SOURCE_DIR ../${MATH_LIB})
add_subdirectory(${${MATH_LIB}_SOURCE_DIR} ${CMAKE_BINARY_DIR}/${MATH_LIB})

include_directories(
        ${${MATH_LIB}_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        CACHE INTERNAL "Path to dependencies folder")

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(gmock)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/unit_tests/*.cpp)
add_gmock_test(${MATH_LIB}_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(${MATH_LIB}_tests ${MATH_LIB})

include(benchmark)

file(GLOB BENCHMARK_SOURCE_FILES ${SOURCE_DIR}/benchmark/*.cpp)
add_benchmark(${MATH_LIB}_benchmark ${BENCHMARK_SOURCE_FILES})
target_link_libraries(${MATH_LIB}_benchmark ${MATH_LIB})