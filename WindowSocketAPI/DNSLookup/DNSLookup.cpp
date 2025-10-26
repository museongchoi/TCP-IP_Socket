#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32")

using namespace std;

int main()
{
	// �ʱ�ȭ �ܰ�
	// winsock DLL�� �޸𸮿� �ε��ϰ� ����� �غ� ��
	// wonsock 2.2 ���� ��û
	WSAData wsaData; // ����ü : ���� ����, �ý��� ���� ��
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WinSock �ʱ�ȭ ����" << "\n";
		return 1;
	}

	hostent* hostinfo = gethostbyname("test.com"); // getaddrinfo()
	if (!hostinfo)
	{
		cout << "DNS ��ȸ ����" << "\n";
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

