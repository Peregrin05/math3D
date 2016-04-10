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

include(gmock)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
add_gmock_test(tests ${SOURCE_FILES})
target_link_libraries(tests math3D)
