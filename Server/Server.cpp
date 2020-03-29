#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#pragma comment(lib,"ws2_32.lib" )


typedef struct clientInfo {
	int index;
	void* data;
}thestruct;

unsigned int __stdcall ServClient(void* s) {
	
	struct clientInfo* p = (struct clientInfo*) s;
	SOCKET* client = (SOCKET*)p->data;
	SOCKET Client = *client;

	int num = 0;
	char number[1];

	while (true) {
		
		
		srand(time(NULL));
		num = (rand() % 10);
		num += p->index * 10;
		std::cout << num << std::endl;
		number[0] = num;
		send(Client, number, sizeof(number), 0);
		Sleep(1000);
	}

	return 0;
}

int main(int argc, char* argv[]) {

	WSADATA wsaData;
	int iResult;
	int index = 0;
	sockaddr_in addr;
	SOCKET sock, client;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(2222);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 

	if (iResult) {

		printf("WSA startup failed");
		return 0;
	}


	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET) {

		printf("Invalid socket");
		return 0;
	}

	iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));

	if (iResult) {

		printf("bind failed %u", GetLastError());

		return 0;
	}

	iResult = listen(sock, SOMAXCONN);

	if (iResult) {

		printf("iResult failed %u", GetLastError());

		return 0;
	}

	while (client = accept(sock, 0, 0)) {
		
		index++;
		thestruct clInfo;
		clInfo.index = index;
		clInfo.data = (void*)&client;

		if (client == INVALID_SOCKET) {
			printf("invalid client socket %u", GetLastError());
			continue;
		}

		_beginthreadex( 0, 0, ServClient, (void*)&clInfo, 0, 0);

	}

	return 0;
}