cmake_minimum_required(VERSION 3.3)
project(TP_algo4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Intersection.h MultiPoly.h Point.h Polygon.h Rectangle.h Segment.h Shape.h Union.h Polygon.cpp Point.cpp MultiPoly.cpp Intersection.cpp Rectangle.cpp Segment.cpp Shape.cpp Union.cpp)
add_executable(TP_algo4 ${SOURCE_FILES})