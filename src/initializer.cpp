#include "initializer.h"
#include <Python.h>
#ifdef _WIN32
#include <Windows.h>
#elif defined __APPLE__

#endif
#include "utils.h"
#include <vector>



initializer::initializer()
{
	

#ifdef _WIN32
#include <Windows.h>
		SetDllDirectory(TEXT("python37\\"));
#elif defined __APPLE__

#endif
	auto combinePaths = [](std::vector<std::string> paths,std::string sep=";") {
		std::string preparedPath = "";
		for (int i = 0; i < paths.size(); i++) {
			preparedPath += get_executable_dir()+paths[i];
			if (i != paths.size() - 1) {
				preparedPath += sep;
			}
		}
		return string2wstring(preparedPath);
	};

		Py_SetPythonHome(string2wstring(get_executable_dir()).c_str());
#ifdef _WIN32
		Py_SetPath(combinePaths({"","\\python37.zip","\\site-packages"}).c_str());
#elif defined __APPLE__
		Py_SetPath(combinePaths({"","/python37.zip","/site-packages","/lib-dynload"},":").c_str());
#endif
		Py_Initialize();

		PyRun_SimpleString("import sys");
		PyRun_SimpleString("print(sys.path)");

}

initializer::~initializer()
{
	
	Py_Finalize();
	
}
