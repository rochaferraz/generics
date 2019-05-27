cmake_minimum_required(VERSION 2.8.9)
project(generic_algorithms_library)

include_directories("inc/" "googletest/googletest/include/" "googletest/googlemock/include/")

file(GLOB SANDBOX "sandbox/*.c")
file(GLOB SOURCES "src/*.c")
file(GLOB TESTS "tst/*.cc")

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -isystem -pthread -Wall")
set(GCC_COVERAGE_LINK_FLAGS    "")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_library(TEST_LIBRARY gtest "googletest/lib")
find_library(MOCK_LIBRARY gmock "googletest/lib")

add_executable(tests ${TESTS} ${SOURCES})
add_test(generalTests tests)

add_executable(sbox ${SANDBOX} ${SOURCES})
add_library(generics STATIC ${SOURCES})
target_link_libraries(tests LINK_PUBLIC ${TEST_LIBRARY} ${MOCK_LIBRARY})
