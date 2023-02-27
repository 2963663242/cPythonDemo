

if(MSVC)
set(UTILS_CPP utils_win.cpp)
set(PLATFORM win)
set(LINK_LIBRARY_DIR lib)
set(LINK_LIBRARY python37 python3)
elseif(APPLE)
set(UTILS_CPP utils_mac.cpp)
set(PLATFORM mac)
set(LINK_LIBRARY_DIR bin)
set(LINK_LIBRARY ${CMAKE_SOURCE_DIR}/sdk/${PLATFORM}/${LINK_LIBRARY_DIR}/Python "-framework CoreFoundation")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/x64)
set(OUTDIR ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE})
endif()

add_executable(cPython 
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/initializer.h 
	${CMAKE_CURRENT_SOURCE_DIR}/initializer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils.h
	${CMAKE_CURRENT_SOURCE_DIR}/${UTILS_CPP}
	)

#添加头文件目录

target_include_directories(cPython PUBLIC ${CMAKE_SOURCE_DIR}/sdk/${PLATFORM}/include)

# 添加库目录
target_link_directories(cPython PUBLIC ${CMAKE_SOURCE_DIR}/sdk/${PLATFORM}/${LINK_LIBRARY_DIR})

# 链接动态库
target_link_libraries(cPython PUBLIC ${LINK_LIBRARY})

if(MSVC)
	# 后处理脚本，将sdk bin目录复制到生成文件夹
	add_custom_command(
	TARGET cPython POST_BUILD
	COMMAND  xcopy "\"${CMAKE_SOURCE_DIR}/sdk/win/bin\"" "$(Outdir)" /E /Y
	)

	# 设置vs调试目录
	set_target_properties(cPython PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
elseif(APPLE)
	# 后处理脚本，将sdk bin目录复制到生成文件夹
	add_custom_command(
	TARGET cPython POST_BUILD
	COMMAND  cp -r ${CMAKE_SOURCE_DIR}/sdk/${PLATFORM}/bin/* ${OUTDIR})
endif()