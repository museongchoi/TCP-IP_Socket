﻿#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32")

int main()
{
	FILE* OutputFile = fopen("../Assets/pororo_copy.png", "wb");

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ListenSockAddr;
	ZeroMemory(&ListenSockAddr, 0);
	ListenSockAddr.sin_family = PF_INET;
	//ListenSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(PF_INET, "127.0.0.1", (void*)&(ListenSockAddr.sin_addr.s_addr));
	ListenSockAddr.sin_port = htons(30000);

	bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, 0);

	struct sockaddr ClientSockAddr;
	ZeroMemory(&ClientSockAddr, 0);
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	char Buffer[4096] = { 0, };
	size_t WriteSize = 0;
	int RecvByte = 0;

	do
	{
		RecvByte = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		WriteSize = fwrite(Buffer, sizeof(char), RecvByte, OutputFile);
	} while (RecvByte > 0);

	fclose(OutputFile);
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}
