cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)



# 添加解决方案名称
project(1_1_hello_world)

# 设置c++17
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else() # gcc clang
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif(MSVC)

# 设置Release or Debug 默认值
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(src)