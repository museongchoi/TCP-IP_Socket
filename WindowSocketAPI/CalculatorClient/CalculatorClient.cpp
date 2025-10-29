#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <string>
#include <random>

using namespace std;

#pragma comment(lib, "ws2_32")



int main()
{
	char Operatror[5] = { '+', '-', '*', '/', '%' };

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, 10000);
	uniform_int_distribution<int> dist2(0, 4);


	return 0;
}