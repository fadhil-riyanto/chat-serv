cmake_minimum_required(VERSION 3.6)
PROJECT(chat-serv)

set(CMAKE_BUILD_TYPE, Debug)

SET(soure_library
    src/parsecmd.cpp
)

ADD_LIBRARY(libchat-serv STATIC "${soure_library}")
add_compile_options("-g")

add_executable(chat-serv-source main.cpp)
target_link_libraries(chat-serv-source libchat-serv)
set_target_properties(chat-serv-source PROPERTIES OUTPUT_NAME "socket-server")