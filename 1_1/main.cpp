#include <Python.h>
#include "utils/utils.h"
#include <iostream>
using namespace std;
void call_main();

int main(){

	Py_SetPythonHome(get_executable_dir_w().c_str());
	Py_Initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(std::string("sys.path.insert(0,r'"+get_executable_dir()+"')").c_str());

    call_main();
	
	Py_Finalize();
}




void call_main() {
	char* result;
	PyObject* pModule = PyImport_ImportModule("test");
	
	if (pModule == NULL) {
		PyErr_Print();
		cout << "module not found" << endl;
		return ;
	}

	PyObject* pFunc = PyObject_GetAttrString(pModule, "hello");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		PyErr_Print();
		cout << "not found function init" << endl;
		return ;
	}
	
	PyObject* pReturn = PyObject_CallObject(pFunc, NULL);
	PyErr_Print();
}
