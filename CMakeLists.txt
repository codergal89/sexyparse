cmake_minimum_required(VERSION "3.14.0")
project("sexyparse"
  LANGUAGES CXX
  VERSION "1.0.0"
)

include("CTest")
include("FetchContent")

### Catch 2

FetchContent_Declare("Catch2"
  GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
  GIT_TAG "v2.13.2"
)
FetchContent_MakeAvailable("Catch2")

list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/contrib")

include("Catch")

### Library

add_library("${PROJECT_NAME}" INTERFACE)

target_sources("${PROJECT_NAME}" INTERFACE
  "include/sexytime.hpp"
)

target_compile_features("${PROJECT_NAME}" INTERFACE
  "cxx_std_17"
)

add_library("SexyParse::SexyParse" ALIAS "${PROJECT_NAME}")

### Tests

add_executable("${PROJECT_NAME}-tests"
  "test/source/tests.cpp"
)

target_compile_features("${PROJECT_NAME}-tests" PRIVATE
  "cxx_std_17"
)

target_link_libraries("${PROJECT_NAME}-tests" PRIVATE
  "SexyParse::SexyParse"
  "Catch2::Catch2"
)

set_target_properties("${PROJECT_NAME}-tests" PROPERTIES
  CXX_EXTENSIONS OFF
  CXX_STANDARD_REQUIRED YES
)

catch_discover_tests("${PROJECT_NAME}-tests")