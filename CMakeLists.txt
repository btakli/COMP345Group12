cmake_minimum_required(VERSION 3.21)
project(COMP345Group12)

set(CMAKE_CXX_STANDARD 14)

include_directories(../../Winter2022/comp345/CmakeBackup)

add_executable(COMP345Group12
        Player.cpp
        Player.h
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        Orders.cpp
        Orders.h
        Map.cpp
        Map.h
        Main.cpp
        )
