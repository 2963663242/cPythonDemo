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
ifend()

# 添加源文件路径

file(GLOB SOURCEFILE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils)
set(UTILS_FILE ${UTILS_DIR}/utils.h ${UTILS_DIR}/utils.cpp)
message(STATUS "UTILS_DIR=${UTILS_DIR}")
if(MSVC)
	set(UTILS_FILE ${UTILS_FILE} ${UTILS_DIR}/utils_win.cpp)
else()
	set(UTILS_FILE ${UTILS_FILE} ${UTILS_DIR}/utils_mac.cpp)
endif()

set(SOURCEFILE ${SOURCEFILE} ${UTILS_FILE})
message(STATUS "SOURCEFILE=${SOURCEFILE}")

# 添加可执行文件项目1_1_hello_world
add_executable(1_1_hello_world ${SOURCEFILE})


#添加头文件路径
target_include_directories(1_1_hello_world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sdk/include)

# 导入库文件

if(MSVC)
	set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk/win/lib")
	find_library(LIBRARYS python37 ${LIB_DIR} REQUIRED)
else()
	set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk/mac/bin")
	set(LIBRARYS  ${LIB_DIR}/Python "-framework CoreFoundation")
endif()
message(STATUS "PYTHON_LIBRARYS=${PYTHON_LIBRARYS}")

target_link_libraries(1_1_hello_world ${LIBRARYS})

message(STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
# 编写后处理脚本，将库复制到生成目录
IF (WIN32)
add_custom_command(
  TARGET 1_1_hello_world POST_BUILD
  COMMAND xcopy  "\"${CMAKE_CURRENT_SOURCE_DIR}/sdk/win/bin\"" "\"$(OutDir)\""  /E /Y
  )
ELSE()
  if(CMAKE_GENERATOR MATCHES "Xcode")
      set(OUTDIR ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/Debug)
  endif()
    add_custom_command(
  TARGET 1_1_hello_world POST_BUILD
  COMMAND cp -r  "\"${CMAKE_SOURCE_DIR}/sdk/mac/bin/\"" "${OUTDIR}"  
  )
ENDIF()

function(print_directory_variables dir)
    # Dump variables:
    get_property(_variableNames DIRECTORY ${dir} PROPERTY VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        get_directory_property(_variableValue DIRECTORY ${dir} DEFINITION ${_variableName})
        message(STATUS "DIR ${dir}: ${_variableName}=${_variableValue}")
    endforeach()
endfunction(print_directory_variables)

# for example
print_directory_variables(.)