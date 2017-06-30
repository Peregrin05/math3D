cmake_minimum_required(VERSION 2.8.4)
project(flash_math_project)

set (CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set (CMAKE_DISABLE_SOURCE_CHANGES ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

enable_testing()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/src)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/unit_tests/*.cpp)
add_executable(flash_math_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(flash_math_tests ${CONAN_LIBS})

