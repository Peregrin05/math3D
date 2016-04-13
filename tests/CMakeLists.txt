cmake_minimum_required(VERSION 2.8.4)
project(tests)

enable_testing()

set (math3D_SOURCE_DIR ../math3D)
add_subdirectory(${math3D_SOURCE_DIR} ${CMAKE_BINARY_DIR}/math3D)

include_directories(
        ${math3D_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        CACHE INTERNAL "Path to dependencies folder")

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(gmock)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/unit_tests/*.cpp)
add_gmock_test(math3D_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(math3D_tests math3D)

include(benchmark)

file(GLOB BENCHMARK_SOURCE_FILES ${SOURCE_DIR}/benchmark/*.cpp)
add_benchmark(math3D_benchmark ${BENCHMARK_SOURCE_FILES})
target_link_libraries(math3D_benchmark math3D)