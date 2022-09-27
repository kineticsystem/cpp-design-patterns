cmake_minimum_required(VERSION 3.22.1)
project(Patterns VERSION 0.1.0 LANGUAGES CXX)
include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Tell CMake to look for Qt components.
find_package(Qt5 REQUIRED COMPONENTS Core)

set (SRC
    Main.cpp
    builder/StepBuilder1.h
    builder/StepBuilder2.h
    builder/StepBuilder3.h
    builder/StepBuilder4.h
    factory/Factory1.h
    injection/Injection1.h
    injection/Injection2.h
    injection/Injection3.h
    injection/Injection4.h
    injection/Injection5.h
    injection/Injection6.h
    injection/Injection7.h
    injection/Injection8.h
    pimpl/Widget.h
    pimpl/Widget.cpp
    pimpl/Widget_p.h
    pimpl/Label.h
    pimpl/Label_p.h
    pimpl/Label.cpp
    mvc/ModelViewController1.h
    mvc/ModelViewController2.h
)

add_executable(Patterns ${SRC})
target_compile_features(Patterns
    PUBLIC cxx_std_20
)

# Tell CMake what components are required by the application.
target_link_libraries(Patterns PRIVATE Qt5::Core)
