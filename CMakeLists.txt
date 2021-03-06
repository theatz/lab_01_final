cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" ON)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.218.tar.gz"
        SHA1 "9a3594a61227967fb92159339ba326701b287b19"
)

project(parser)
#string(APPEND CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/GCC-9FIX.cmake")
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json 3.2.0 CONFIG REQUIRED)

add_library(lab-01 STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Student.cpp
        )
add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

target_include_directories(lab-01
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_link_libraries(lab-01 nlohmann_json::nlohmann_json)

target_link_libraries(tests GTest::main lab-01)

enable_testing()
add_test(NAME unit_tests COMMAND tests)

if(BUILD_COVERAGE)
  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)
  add_coverage(lab-01)
  add_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()
