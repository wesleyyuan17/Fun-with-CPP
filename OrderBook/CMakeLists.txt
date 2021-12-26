# defining projects
cmake_minimum_required(VERSION 3.19.1)
project(OrderBook)

# including definitions
include_directories(include)

# building main executable for project
add_executable(OrderBook main.cpp)

# testing with Catch2
file(GLOB TESTS "tests/*.cpp")
file(GLOB SOURCES "src/*.cpp")
message(STATUS "${TESTS}, ${SOURCES}")
add_executable(tests ${TESTS} ${SOURCES})

find_package(Catch2 REQUIRED)
target_link_libraries(tests PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

enable_testing()