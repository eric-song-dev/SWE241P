# CMake minimal version
cmake_minimum_required(VERSION 3.10)

# Project name
project(AnagramAssignment)

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

# Create library target for the assignment functionality
add_library(anagram_lib
    src/AnagramGrouper.cpp
    src/SortUtils.cpp
    include/AnagramGrouper.h
    include/SortUtils.h
)
target_include_directories(anagram_lib PUBLIC include)

# Add the main executable
add_executable(
    anagram_app
    src/Main.cpp
)
target_link_libraries(anagram_app PRIVATE anagram_lib)

# Add test executable
add_executable(
    anagram_tests
    tests/anagram_test.cpp
)
target_link_libraries(anagram_tests
    PRIVATE
    anagram_lib
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
option(ENABLE_GTEST_DISCOVER_ON_BUILD "Run gtest_discover_tests at build time" OFF)

if(ENABLE_GTEST_DISCOVER_ON_BUILD)
    gtest_discover_tests(anagram_tests)
else()
    add_test(NAME anagram_tests COMMAND anagram_tests)
endif()

# Optional: Define output directory for binary
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
