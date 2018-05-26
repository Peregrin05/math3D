cmake_minimum_required(VERSION 2.8.4)
project(flash_math_project)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif()

set(FLASH_MATH_PATH "" CACHE PATH "Path to flash_math project root")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(LINK_LIBS CONAN_PKG::gtest)

if("${FLASH_MATH_PATH}" STREQUAL "")
    list(APPEND LINK_LIBS CONAN_PKG::flash_math)
else()
    set(SUFFIX "")
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(SUFFIX "d")
    endif()
    list(APPEND LINK_LIBS "flash_math${SUFFIX}")
    add_subdirectory(${FLASH_MATH_PATH} ${CMAKE_CURRENT_BINARY_DIR}/flash_math)
    get_property(flash_math_INCLUDE_DIRECTORIES TARGET flash_math PROPERTY INCLUDE_DIRECTORIES)
    include_directories(${flash_math_INCLUDE_DIRECTORIES})
    link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

enable_testing()

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/src)

file(GLOB UNIT_TEST_SOURCE_FILES ${SOURCE_DIR}/unit_tests/*.cpp)
add_executable(flash_math_tests ${UNIT_TEST_SOURCE_FILES})
target_link_libraries(flash_math_tests ${LINK_LIBS})
target_include_directories(flash_math_tests PUBLIC ${SOURCE_DIR})

