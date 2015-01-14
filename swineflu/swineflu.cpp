// swineflu.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include "svchost.cpp"

void adminpriv()
{
	printf("admin method called");
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("wear your mask please\n");
	adminpriv();
	logger();
	return 0;
}


