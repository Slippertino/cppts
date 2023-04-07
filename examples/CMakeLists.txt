cmake_minimum_required(VERSION 3.4)

project(cppts_examples)

include("../cmake/utils.cmake")

file(GLOB_RECURSE ${EX_HEADERS} "${CMAKE_CURRENT_LIST_DIR}/*.hpp")

macro(declare_example EX_NAME EX_TARGET)
    add_executable(${EX_NAME})
    target_sources(${EX_NAME} PRIVATE ${EX_TARGET})
    target_include_directories(${EX_NAME} PRIVATE ${EX_HEADERS})
    target_link_libraries(${EX_NAME} PRIVATE cppts::cppts)

    if(NOT PROJECT_IS_TOP_LEVEL)
        win_copy_deps_to_target_dir(${EX_NAME} cppts::cppts)
    else()
        message(FATAL_ERROR "top level is not supported")
    endif()
endmacro()

declare_example(simple_task simple_task.cpp)
declare_example(custom_task custom_task.cpp)
declare_example(proxy_scheduler_usage proxy_scheduler_usage.cpp)