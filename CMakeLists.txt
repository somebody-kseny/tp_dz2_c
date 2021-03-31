cmake_minimum_required(VERSION 3.0)
project(SecondDZ)

add_compile_options("--coverage")

set(CMAKE_C_STANDART 11)
set(CMAKE_C_STANDART_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -ggdb3 -fprofile-generate -fprofile-arcs -ftest-coverage -fPIC -O0")

include_directories ("./include") 

add_library( consistent_static_lib STATIC ${PROJECT_SOURCE_DIR}/consistent.c)
add_executable(main_consistent ${PROJECT_SOURCE_DIR}/main.c )
target_link_libraries(main_consistent consistent_static_lib)

add_library( parallel_shared_lib SHARED ${PROJECT_SOURCE_DIR}/parallel.c )	
add_executable(main_parallel ${PROJECT_SOURCE_DIR}/main.c )
target_link_libraries(main_parallel parallel_shared_lib)


# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic -ggdb3 ")

set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb3")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${GTEST_INCLUDE_DIR})

add_executable(tests_gcovr_parall tests_lib.cpp )
target_link_libraries(tests_gcovr_parall ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_gcovr_parall parallel_shared_lib)
target_link_libraries(tests_gcovr_parall gcov)

add_executable(tests_gcovr_cons tests_lib.cpp )
target_link_libraries(tests_gcovr_cons ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests_gcovr_cons consistent_static_lib)
target_link_libraries(tests_gcovr_cons gcov)
