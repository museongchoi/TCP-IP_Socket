#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32")

using namespace std;

int main()
{
	// 초기화 단계
	// winsock DLL을 메모리에 로드하고 사용할 준비를 함
	// wonsock 2.2 버전 요청
	WSAData wsaData; // 구조체 : 버전 정보, 시스템 상태 등
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WinSock 초기화 실패" << "\n";
		return 1;
	}

	hostent* hostinfo = gethostbyname("test.com"); // getaddrinfo()
	if (!hostinfo)
	{
		cout << "DNS 조회 실패" << "\n";
		return 1;
	}
	
	cout << "hostname : " << hostinfo->h_name << "\n";

	for (int i = 0; hostinfo->h_addr_list[i]; ++i)
	{
		IN_ADDR Addr = *(IN_ADDR*)(hostinfo->h_addr_list[i]);
		char ip[30] = { 0, };
		inet_ntop(AF_INET, &Addr, ip, sizeof(ip));
		cout << "IP : " << ip << "\n";
	}

	WSACleanup();
	return 0;
}

