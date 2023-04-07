cmake_minimum_required(VERSION 3.4)

project(cppts_tests)

include("../cmake/utils.cmake")

file(GLOB_RECURSE ${CPPTS_TESTS_SOURCES} "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

macro(add_cppts_test TEST_NAME)
    add_executable(${TEST_NAME}_tests ${TEST_NAME}_tests.cpp)
    target_link_libraries(${TEST_NAME}_tests
        PRIVATE 
            cppts::cppts
            GTest::GTest
    )

    add_test(NAME cppts_${TEST_NAME}_tests COMMAND ${TEST_NAME}_tests)
    set_property(TARGET ${TEST_NAME}_tests PROPERTY FOLDER "tests")

    if(NOT PROJECT_IS_TOP_LEVEL)
        win_copy_deps_to_target_dir(${TEST_NAME}_tests cppts::cppts GTest::GTest)
    else()
        message(FATAL_ERROR "top level is not supported")
    endif()

    gtest_discover_tests(${TEST_NAME}_tests)
endmacro()

include(GoogleTest)

add_cppts_test(simple)