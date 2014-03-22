#include <iostream>
#include <WinSock2.h>

#pragma once
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

u_long resolveHost(const string &host); // funkcja, dziêki której u¿ytkownik ma dowolnoœæ jeœli chodzi o wybór adres, czy nazwa hosta


int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKADDR_IN saddr;
	SOCKET sock;
	const char *helloMessage = "Test serwer, wersja 1.0\n";

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset((void*)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(10000);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != SOCKET_ERROR)
	{
		if (listen(sock, 1) != SOCKET_ERROR)
		{
			for (int i = 0; i < 5; i++) {
				SOCKET client = accept(sock, NULL, NULL);

				send(client, helloMessage, strlen(helloMessage), 0);
				closesocket(client);
			}
		}
	}

	closesocket(sock);
	WSACleanup();
	system("pause");
	return 0;
}

u_long resolveHost(const string &host){
	LPHOSTENT hostEntry = gethostbyname(host.c_str());

	if (!hostEntry){
		unsigned int addr = inet_addr(host.c_str());
		hostEntry = gethostbyaddr((char *)&addr, 4, AF_INET);

		if (!hostEntry){
			cout << "the host was not found" << endl;
			exit(2);
		}
	}

	return *((int*)*hostEntry->h_addr_list);
}