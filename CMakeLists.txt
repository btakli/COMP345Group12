cmake_minimum_required(VERSION 3.21)
project(Backup2022.02.09)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Backup2022.02.09

        Player.cpp
        Player.h
        PlayerDriver.cpp

        OrdersList.cpp OrdersList.h Territory.cpp Territory.h Hand.cpp Hand.h Order.cpp Order.h)
