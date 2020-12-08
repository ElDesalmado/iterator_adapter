cmake_minimum_required(VERSION 3.18)
project(IterAdapter)

set(CMAKE_CXX_STANDARD 11)

add_library(IterAdapter INTERFACE)
target_include_directories(IterAdapter INTERFACE include)

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