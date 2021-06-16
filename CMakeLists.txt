cmake_minimum_required(VERSION 3.5)

project(Patterns LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (SRC
    Main.cpp
    builder/StepBuilder1.h
    builder/StepBuilder2.h
    builder/StepBuilder3.h
    factory/Factory1.h
    injection/Injection1.h
    injection/Injection2.h
    injection/Injection3.h
    injection/Injection4.h
    injection/Injection5.h
    injection/Injection6.h
    pimpl/Car.h
    pimpl/Car.cpp
    pimpl/CarImpl.h
    pimpl/CarImpl.cpp
)

add_executable(Patterns ${SRC})
