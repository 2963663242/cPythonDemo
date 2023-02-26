
add_executable(cPython 
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/initializer.h 
	${CMAKE_CURRENT_SOURCE_DIR}/initializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils.h
	${CMAKE_CURRENT_SOURCE_DIR}/utils_win.cpp
	)

#添加头文件目录

target_include_directories(cPython PUBLIC ${CMAKE_SOURCE_DIR}/sdk/win/include)

# 添加库目录
target_link_directories(cPython PUBLIC ${CMAKE_SOURCE_DIR}/sdk/win/lib)

# 链接动态库
target_link_libraries(cPython PUBLIC python37 python3)

# 后处理脚本，将sdk bin目录复制到生成文件夹
add_custom_command(
TARGET cPython POST_BUILD
COMMAND  xcopy "\"${CMAKE_SOURCE_DIR}/sdk/win/bin\"" "$(Outdir)" /E /Y
)

# 设置vs调试目录
set_target_properties(cPython PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
