// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Common.h"
#include "logger.h"

DWORD WINAPI ThreadMain(LPVOID lpParameter)
{
	wchar_t buffer[200];

	// Format and print various data: 
	_swprintf_s_l(buffer, 200, L"Current process id: %d next process id: %d\n", _get_current_locale(), 0, 0);
	MessageBox(NULL, buffer, L"Injected!", MB_OK); 

	logger();

	//fopen("C:\\Temp\\a.txt", "a+");

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	// get next process to infect

	int next_process_id = 0;
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		int current_process_id = GetCurrentProcessId();
		//next_process_id = MyInjecteeFuncs::getNextProcessID(current_process_id);

		/*DisableThreadLibraryCalls(hInst); */
		DWORD  dwThreadId;


		HANDLE hThread = CreateThread(
			NULL, 0, ThreadMain, NULL, 0, &dwThreadId); 

		
	

		//logger();

	
		

		//CreateThread(NULL, 0, Foo::MyThreadFunction, foo, 0L, NULL);


		//if (next_process_id != 0) { 
			//MyInjecteeFuncs::inject(next_process_id);
		//}
		// address of write file 77E311CC

	} 

	// This is the last process don't unload.
	BOOL last_process = (next_process_id == 0); 
	return last_process;
}

