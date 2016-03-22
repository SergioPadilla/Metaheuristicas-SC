cmake_minimum_required(VERSION 3.3)
project(SeleccionCaracteristicas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileReader/FileReaderARFF.cpp FileReader/FileReaderARFF.h Utils/struct.h)
add_executable(SeleccionCaracteristicas ${SOURCE_FILES})