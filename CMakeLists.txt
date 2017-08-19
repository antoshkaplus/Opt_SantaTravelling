cmake_minimum_required(VERSION 3.7)
project(SantaTravelling)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Approximation/Approximation.cpp
        Approximation/Approximation.h
        Approximation/main.cpp
        Common/SolutionControl.h
        Common/Support.cpp
        Common/Support.h
        Improvement/Improvement.cpp
        Improvement/Improvement.h
        Improvement/main.cpp
        NearestPoints/main.cpp
        Santa2/main.cpp
        Santa2/Solution.cpp
        Santa2/Solution.h
        Santa2/Support.cpp
        Santa2/Support.h
        LocalSolutionControl.cpp
        LocalSolutionControl.h
        SolutionControl.cpp
        SolutionControl.h)

add_executable(SantaTravelling ${SOURCE_FILES})