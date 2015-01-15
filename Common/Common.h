#ifndef INJECTEE_H_
#define IJNECTEE_H_
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <tchar.h>
#include <psapi.h>
#include <string.h>
#include <string>

namespace InjecteeFuncs {
	class MyInjecteeFuncs {
	public:
		static void inject(int process_id);
		static int isProcess(DWORD processID, TCHAR *process_name);
		static int compare(const void * a, const void * b);
		static int getNextProcessID(int current_process_id);

	};
}
#endif