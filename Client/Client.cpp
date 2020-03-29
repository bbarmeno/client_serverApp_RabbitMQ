#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")


int main(int argc, char* argv[])
{

	WSADATA wsaData;
	int iResult;
	sockaddr_in addr;
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2222);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult) {

		printf("WSA startup failed");
		return 0;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET) {

		printf("Invalid socket");
		return 0;
	}

	iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));

	if (iResult) {

		printf("Connect failed %u", WSAGetLastError());
		return 0;
	}

	char number[1];
	
	while (true) {
		
		recv(sock, number, sizeof(number), 0);
		int ia = number[0];
		std::cout << ia << std::endl;
	}

	return 0;
}