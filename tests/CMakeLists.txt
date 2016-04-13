cmake_minimum_required(VERSION 2.8.4)
project(tests)

set (CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++14 -Wall -Wno-missing-braces")
# TODO: ".." part should be gone from path, e.g. modules should be handled in root cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules)

enable_testing()

set (math3D_SOURCE_DIR ../math3D)
add_subdirectory(${math3D_SOURCE_DIR} ${CMAKE_BINARY_DIR}/math3D)

include_directories(
        ${math3D_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        CACHE INTERNAL "Path to dependencies folder")

include(gmock)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
set (UNIT_TEST_SOURCE_FILES
        ${SOURCE_DIR}/Vector3DTest.cpp
        ${SOURCE_DIR}/Matrix3DTest.cpp
        ${SOURCE_DIR}/EulerAnglesTest.cpp
        ${SOURCE_DIR}/QuaternionTest.cpp
        ${SOURCE_DIR}/OrientationTest.cpp
        ${SOURCE_DIR}/unit_tests.cpp)

add_gmock_test(math3D_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(math3D_tests math3D)

include(benchmark)

set (BENCHMARK_SOURCE_FILES
        ${SOURCE_DIR}/benchmark_tests.cpp)
add_benchmark(math3D_benchmark ${BENCHMARK_SOURCE_FILES})
target_link_libraries(math3D_benchmark math3D)