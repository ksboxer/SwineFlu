#ifndef SWINENETWORKING_H
#define SWINENETWORKING_H
#include<windows.h>
#include<stdio.h>
#include<winuser.h>
#include<windowsx.h>
namespace SwineNetworking {
	class Networking {
	public:
		static int __cdecl extract(char *sendbuf, int length, int *bytes_sent);
		static int __cdecl sendFile(FILE of);
	};
}
#endif