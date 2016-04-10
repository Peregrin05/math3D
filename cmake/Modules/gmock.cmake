find_library(TEST_LIB
        NAMES gtest gmock
        PATHS libs)

# add_gmock_test(<target> <sources>...)
#
# Adds a Google Mock based test executable, <target>, built from <sources> and
# adds the test so that CTest will run it. Both the executable and the test
# will be named <target>.
function(add_gmock_test target)
    add_executable(${target} ${ARGN})
    set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
    target_link_libraries(${target} ${TEST_LIB})
    add_test(${target} ${target})

    add_custom_command(
            TARGET ${target}
            POST_BUILD COMMAND ${target}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Running ${target}" VERBATIM)
endfunction()
