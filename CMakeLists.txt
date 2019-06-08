cmake_minimum_required(VERSION 3.13.1)
project(tatu_library)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include_directories("inc/" "googletest/googletest/include/" "googletest/googlemock/include/")

file(GLOB SANDBOX "sandbox/*.c")
file(GLOB SOURCES "src/*.c")
file(GLOB TESTS "tst/*.cc")

foreach(v ${SOURCES})
    message(STATUS SRC:${v})
endforeach(v)

foreach(v ${TESTS})
    message(STATUS TST:${v})
endforeach(v)

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -g -isystem -pthread -Wall")
set(GCC_COVERAGE_LINK_FLAGS    "")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_library(TEST_LIBRARY gtest "googletest/lib")
find_library(MOCK_LIBRARY gmock "googletest/lib")

#add_library(tatu STATIC ${SOURCES})
add_executable(tatu_tests ${TESTS} ${SOURCES})
target_link_libraries(tatu_tests LINK_PUBLIC ${TEST_LIBRARY} ${MOCK_LIBRARY})

add_executable(tatu_sandbox ${SANDBOX} ${SOURCES})
