cmake_minimum_required(VERSION 3.29)
project(lab0)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab0
    main.cpp reader.cpp
        counter.cpp
        writer.cpp)