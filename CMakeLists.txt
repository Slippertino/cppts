cmake_minimum_required (VERSION 3.4)

project(
    cppts
    VERSION 1.0.0
    DESCRIPTION "C++ Task Scheduler Library"
    LANGUAGES CXX
)

include(cmake/utils.cmake)
include(GNUInstallDirs)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

option(CPPTS_SHARED "Build shared cppts" OFF)
option(CPPTS_BUILD_EXAMPLES "Build cppts examples" ON)
option(CPPTS_BUILD_TESTS "Build tests for cppts" OFF)
option(CPPTS_INSTALL "Generate target for installing cppts" PROJECT_IS_TOP_LEVEL)

if(CPPTS_SHARED)
    set(BUILD_SHARED_LIBS TRUE)
endif()

if(CPPTS_BUILD_TESTS)
    FetchContent_Declare(googletest
        GIT_REPOSITORY                 https://github.com/google/googletest.git
        GIT_TAG                        b796f7d44681514f58a683a3a71ff17c94edb0c1 
        USES_TERMINAL_DOWNLOAD TRUE)
    FetchContent_MakeAvailable(googletest)

    add_library(gtest_int INTERFACE)
    target_link_libraries(gtest_int INTERFACE gtest)
    target_include_directories(gtest_int INTERFACE ${googletest_SOURCE_DIR}/include)

    add_library(GTest::GTest ALIAS gtest_int)

    set_property(TARGET gtest PROPERTY FOLDER "tests/gtest")
    set_property(TARGET gtest_main PROPERTY FOLDER "tests/gtest")
endif()

file(GLOB_RECURSE CPPTS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE CPPTS_INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/cppts/*.hpp"
)

add_library(cppts)
add_library(cppts::cppts ALIAS cppts)

target_sources(cppts 
    PRIVATE 
        ${CPPTS_SOURCES} ${CPPTS_INCLUDES} 
)

set_target_properties(cppts
        PROPERTIES
        VERSION ${${PROJECT_NAME}_VERSION}
        SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
)

target_include_directories(cppts
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cppts
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cppts/cppts>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cppts>
)

install(DIRECTORY cppts DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS cppts
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(CPPTS_BUILD_EXAMPLES)
    message(STATUS "Building cppts examples.")

    add_subdirectory(examples)
endif()

if(CPPTS_BUILD_TESTS)
    message(STATUS "Building cppts tests.")

    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()