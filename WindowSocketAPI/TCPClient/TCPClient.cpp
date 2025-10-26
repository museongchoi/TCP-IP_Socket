#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32")

int main()
{
	// [1] 파일 읽기
	FILE* InputFile = fopen("../Assets/pororo.png", "rb");
	if (!InputFile)
	{
		perror("파일 열기 실패");
		return 1;
	}

	// [2] WinSock 초기화
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// [3] 서버 연결 소켓 생성
	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in ServerSockAddr;
	ZeroMemory(&ServerSockAddr, 0);
	ServerSockAddr.sin_family = PF_INET;
	//ListenSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(PF_INET, "127.0.0.1", (void*)&(ServerSockAddr.sin_addr.s_addr));
	ServerSockAddr.sin_port = htons(30000);

	// [4] 서버 연결
	connect(ServerSocket, (struct sockaddr*)&ServerSockAddr, sizeof(ServerSockAddr));

	// [5] 파일 전송
	char Buffer[4096] = { 0, };
	size_t ReadSize = 0;
	int SendBytes = 0;

	do
	{
		ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), InputFile);
		SendBytes = send(ServerSocket, Buffer, (int)ReadSize, 0);
	} while (ReadSize > 0);


	// [6] 종료
	fclose(InputFile);
	closesocket(ServerSocket);
	WSACleanup();

	cout << "파일 전송 완료\n";

	return 0;
}