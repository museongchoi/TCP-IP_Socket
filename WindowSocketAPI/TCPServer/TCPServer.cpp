#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32")

int main()
{
	// [1] 파일 쓰기 : 수신 데이터를 저장할 파일 스트림 생성
	FILE* OutputFile = fopen("../Assets/pororo_copy.png", "wb");

	// [2] WinSock 초기화
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// [3] 리슨 전용 소켓 생성
	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, 0);

	// 리슨 소켓 주소 구조체
	struct sockaddr_in ListenSockAddr;
	ZeroMemory(&ListenSockAddr, 0);
	ListenSockAddr.sin_family = AF_INET;
	//ListenSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", (void*)&(ListenSockAddr.sin_addr.s_addr));
	ListenSockAddr.sin_port = htons(30000);

	// [4] 리슨 소켓 포트 바인딩
	bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	// [5] 대기 상태 전환
	listen(ListenSocket, 0);

	// 클라이언트 소켓 주소를 저장할 구조체
	struct sockaddr ClientSockAddr;
	ZeroMemory(&ClientSockAddr, 0);
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	// [6] 클라이언트 연결 요청 수락
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	// [7] 데이터 수신
	char Buffer[4096] = { 0, };
	size_t WriteSize = 0;
	int RecvByte = 0;

	do
	{
		RecvByte = recv(ClientSocket, Buffer, sizeof(Buffer), 0);
		WriteSize = fwrite(Buffer, sizeof(char), RecvByte, OutputFile);
	} while (RecvByte > 0);

	// [8] 종료
	fclose(OutputFile);

	closesocket(ClientSocket);
	closesocket(ListenSocket);
	WSACleanup();

	return 0;
}
