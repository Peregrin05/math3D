cmake_minimum_required(VERSION 2.8.4)
project(tests)

include_directories(${SOURCE_DIR})

find_library(TEST_LIB
        NAMES gtest gmock
        PATHS libs
        )

set (math3D_SOURCE_DIR ../math3D)
add_subdirectory(${math3D_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/lib)

include_directories(
        ${math3D_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
add_executable(tests ${SOURCE_FILES})
set_target_properties(tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(tests math3D ${TEST_LIB})