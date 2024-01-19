cmake_minimum_required(VERSION 3.27)
project(WinsockClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(WinsockClient main.cpp
        User.cpp
        User.h
        ClientException.cpp
        ClientException.h
        Command.cpp
        Command.h
        BlogPost.cpp
        BlogPost.h
        Admin.cpp
        Admin.h)
if(MINGW)
    target_link_libraries(WinsockClient ws2_32)
endif()

