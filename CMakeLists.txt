cmake_minimum_required(VERSION 3.8)


set(PROJECT_NAME canTool)
set(SRC_LIST 
		_source/Basic_config.cpp 
		_source/Func_can.cpp
		_source/Func_msg.cpp
		_source/main.cpp
	)

set(CMAKE_CXX_FLAGS -pthread)

project(${PROJECT_NAME})

include_directories(_include)

message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} pthread zcm)

target_link_libraries(${PROJECT_NAME} libusbcan.so)
