cmake_minimum_required(VERSION 3.27)
project(WinsockClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(WinsockClient main.cpp)
if(MINGW)
    target_link_libraries(WinsockClient ws2_32)
endif()

