# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(RecursionBacktrackingAssignment)

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

# Create library target for recursion/backtracking functionality
add_library(recursion_backtracking_lib
    src/NQueensSolver.cpp
    src/PermutationCheck.cpp
    include/NQueensSolver.h
    include/PermutationCheck.h
)
target_include_directories(recursion_backtracking_lib PUBLIC include)

# Add the main executable
add_executable(
    recursion_backtracking_app
    src/Main.cpp
)
target_link_libraries(recursion_backtracking_app PRIVATE recursion_backtracking_lib)

# Add test executable
add_executable(
    recursion_backtracking_tests
    tests/recursion_backtracking_test.cpp
)
target_link_libraries(recursion_backtracking_tests
    PRIVATE
    recursion_backtracking_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)
if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(recursion_backtracking_tests)
else()
    add_test(NAME recursion_backtracking_tests COMMAND recursion_backtracking_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
