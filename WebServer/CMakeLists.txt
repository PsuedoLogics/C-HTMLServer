cmake_minimum_required(VERSION 3.30)
project(WebServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(WebServer main.cpp
        Server.cpp
        Server.h
)
