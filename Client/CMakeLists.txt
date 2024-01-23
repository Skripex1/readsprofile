cmake_minimum_required(VERSION 3.22)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp
        Connection/TCPClient.cpp
        Connection/TCPClient.h
        Requests/TypeRequests.cpp
        Requests/TypeRequests.h
        utils/utils.cpp
        utils/utils.h)
