#define _CRT_SECURE_NO_WARNONGS
#include <iostream>
#include <WinSock2.h>
#include <string>

using namespace std;

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cerr << "socket() failed : " << WSAGetLastError() << "\n";
		WSACleanup();
		return 1;
	}

	return 0;
}