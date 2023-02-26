#include <iostream>
#include <Python.h>
#include "initializer.h"

using namespace std;
initializer  initer;

void call_main() {
	char* result;
	PyObject* pModule = PyImport_ImportModule("test");
	if (pModule == NULL) {
		PyErr_Print();
		cout << "module not found" << endl;
		return;
	}

	PyObject* pFunc = PyObject_GetAttrString(pModule, "main");
	if (!pFunc || !PyCallable_Check(pFunc)) {
		PyErr_Print();
		cout << "not found function init" << endl;
		return;
	}

	PyObject* pReturn = PyObject_CallObject(pFunc, NULL);
	PyErr_Print();
}
void inputArgs(int argc, char** argv) {

	if (argc > 0)
		for (int i = 0; i < argc; i++)
			PyRun_SimpleString((string("sys.argv.append(r'") + argv[i] + "')").c_str());
}
int main(int argc, char** argv)
{

	inputArgs(argc, argv);
	call_main();


	return 0;
}
