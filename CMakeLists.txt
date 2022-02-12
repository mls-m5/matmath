
cmake_minimum_required(VERSION 3.22)

project(MatMath)

add_library(MatMath INTERFACE)

target_include_directories(
    MatMath
    INTERFACE include
    )

target_compile_features(MatMath INTERFACE cxx_std_17)

create_test_sourcelist(
    Tests
    src/math_test.cpp
    FUNCITON
    main)



