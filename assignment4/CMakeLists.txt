# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(GraphAssignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent for downloading Google Test
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Create library target for graph functionality
add_library(graph_lib
    src/Graph.cpp
    src/City.cpp
    include/Graph.h
    include/City.h
)
target_include_directories(graph_lib PUBLIC include)

# Add the main executable
add_executable(
    graph_app
    src/Main.cpp
)
target_link_libraries(graph_app PRIVATE graph_lib)

# Add test executable
add_executable(
    graph_tests
    tests/graph_test.cpp
)
target_link_libraries(graph_tests
    PRIVATE
    graph_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)

if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(graph_tests)
else()
    add_test(NAME graph_tests COMMAND graph_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
