set (BENCHMARK_DIR ${DEPENDENCIES_DIR}/benchmark)

add_subdirectory(${BENCHMARK_DIR} ${CMAKE_BINARY_DIR}/benchmark)
set_target_properties(benchmark PROPERTIES COMPILE_FLAGS " -w")
target_compile_definitions(benchmark PRIVATE CMAKE_BUILD_TYPE=Release BENCHMARK_ENABLE_LTO=true)

include_directories(${BENCHMARK_DIR}/include)

# add_benchmark(<target> <sources>...)
#
# Adds an executable for benchmark testing, <target>, built from <sources>. The executable
# will be named <target>.
function(add_benchmark target)
    add_executable(${target} ${ARGN})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(${target} PROPERTIES COMPILE_FLAGS " -O0")
    target_link_libraries(${target} benchmark)

#    add_custom_command(
#            TARGET ${target}
#            POST_BUILD COMMAND ${target}
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#            COMMENT "Running ${target}" VERBATIM)
endfunction()
