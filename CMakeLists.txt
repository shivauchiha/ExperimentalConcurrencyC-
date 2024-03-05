cmake_minimum_required(VERSION 3.9.1)
project(concurrency)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#chapter1
add_executable(ch1.1 Chapter1/exp1.cpp)
add_executable(ch1.2 Chapter1/exp2.cpp)
add_executable(ch1.3 Chapter1/exp3.cpp)
add_executable(ch1.4 Chapter1/exp4.cpp)
add_executable(ch1.5 Chapter1/exp5.cpp)
target_link_libraries(ch1.1  PRIVATE Threads::Threads)
target_link_libraries(ch1.2  PRIVATE Threads::Threads)
target_link_libraries(ch1.3  PRIVATE Threads::Threads)
target_link_libraries(ch1.4  PRIVATE Threads::Threads)
target_link_libraries(ch1.5  PRIVATE Threads::Threads)
#chapter2

add_executable(ch2.1 Chapter2/exp1.cpp)
add_executable(ch2.2 Chapter2/exp2.cpp)

target_link_libraries(ch2.1  PRIVATE Threads::Threads)
target_link_libraries(ch2.2  PRIVATE Threads::Threads)

#chapter3

add_executable(ch3.1 Chapter3/exp1.cpp)

target_link_libraries(ch3.1  PRIVATE Threads::Threads)

