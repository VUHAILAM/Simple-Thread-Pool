cmake_minimum_required(VERSION 3.0)

project(thread_pool)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(
    thread_pool
    ThreadPool.cpp
    main.cpp
)