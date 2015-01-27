cmake_minimum_required (VERSION 2.6)
project (SimpleLog)

ADD_DEFINITIONS(
    	-std=c++11
)
add_executable(SimpleLog main.cpp
                            SimpleLog.h
                            SimpleLog.cpp)
