#include "utils.h"
#include <Windows.h>
#include <comutil.h>
using namespace std;
#pragma comment(lib , "comsupp.lib")
#pragma comment(lib , "comsuppw.lib")
std::string get_executable_dir() {
	 std::string exeDir = "";
	char szExeName[MAX_PATH] = {0,};
	volatile int lastIndex = 0;
	::GetModuleFileNameA(NULL, szExeName, MAX_PATH);
	exeDir = szExeName;
	lastIndex = exeDir.find_last_of("\\");
	exeDir = exeDir.substr(0, lastIndex);
	return exeDir;
}
std::string wstring2string(const wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	string result = pchar;
	return result;
}
std::wstring string2wstring(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}
