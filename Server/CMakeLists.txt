cmake_minimum_required(VERSION 3.22)
project(Server)

set(CMAKE_CXX_STANDARD 17)


add_executable(Server main.cpp
        Connection/TCP.cpp
        Connection/TCP.h
        Connection/TCPClient.cpp
        Connection/TCPClient.h
        DataBase/DB_Manager.cpp
        DataBase/DB_Manager.h
        TypeRequests/TypeRequests.cpp
        TypeRequests/TypeRequests.h
        utils/utils.cpp
        utils/utils.h

)
