cmake_minimum_required(VERSION 3.19.1)
project(OrderBook)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(OrderBook ${SOURCES})

file(GLOB TESTS "tests/*.cpp")
add_executable(tests ${TESTS})

find_package(Catch2 REQUIRED)
target_link_libraries(tests Catch2::Catch2)
enable_testing()
