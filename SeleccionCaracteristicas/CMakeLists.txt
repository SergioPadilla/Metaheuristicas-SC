cmake_minimum_required(VERSION 3.3)
project(SeleccionCaracteristicas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp FileReader/FileReaderARFF.cpp FileReader/FileReaderARFF.h Utils/struct.h K-NN/three_NN.cpp K-NN/three_NN.h Algorithms/Algorithms.cpp Algorithms/Algorithms.h random/random.cpp random/random.h Timer/Timer.cpp Timer/Timer.h)
add_executable(SeleccionCaracteristicas ${SOURCE_FILES})