cmake_minimum_required(VERSION 3.28)
project(money_manage)

set(CMAKE_CXX_STANDARD 23)

add_executable(money_manage main.cpp
        Storage.h
        Storage.cpp
        WinIn.h
        WinIn.cpp
        WinOut.h
        WinOut.cpp
)

target_link_libraries(money_manage libeasyx.a)