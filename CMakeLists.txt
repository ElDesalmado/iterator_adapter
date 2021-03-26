cmake_minimum_required(VERSION 3.7.2 FATAL_ERROR)
project(IterAdapter)

set(CMAKE_CXX_STANDARD 11)

get_directory_property(hasParent PARENT_DIRECTORY)

include(CMakeDependentOption)

# do not build tests if included as a subdirectory
cmake_dependent_option(BUILD_TESTS "Build Tests" ON
        "NOT hasParent" OFF)

add_library(IterAdapter INTERFACE)
target_include_directories(IterAdapter INTERFACE include)

if (BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_executable(test.iterator_adapter test/test_iterator_adapter.cpp)
    target_link_libraries(test.iterator_adapter
            PRIVATE
            IterAdapter
            GTest::GTest
            )

    add_test(NAME test.iterator_adapter
            COMMAND test.iterator_adapter)
endif()

