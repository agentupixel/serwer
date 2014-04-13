#include <iostream>
#include <winsock2.h>
#include <ctime>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	srand(time(0));
	int kto = rand() % 2;
	std::cout << kto << std::endl;
	system("pause");

	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		std::cout << "WSA Initialization failed!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), Socket2 = SOCKET_ERROR;
	if (Socket == INVALID_SOCKET)
	{
		std::cout << "Socket creation failed.\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	SOCKADDR_IN serverInf;
	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(27015);

	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR)
	{
		std::cout << "Unable to bind socket!\r\n";
		WSACleanup();
		system("PAUSE");
		return 0;
	}

	listen(Socket, 2);


	SOCKET TempSock = SOCKET_ERROR;
	while (TempSock == SOCKET_ERROR)
	{
		std::cout << "Waiting for incoming connections...\r\n";
		TempSock = accept(Socket, NULL, NULL);
		//	std::cout << "Client not connected!\r\n\r\n";
	}
	//Socket = TempSock;
	while (Socket2 == SOCKET_ERROR)
	{
		std::cout << "Waiting for incoming connections...\r\n";
		Socket2 = accept(Socket, NULL, NULL);
		//	std::cout << "Client not connected!\r\n\r\n";
	}
	Socket = TempSock;

	std::cout << "Client connected!\r\n\r\n";
	/*
	send i recv operuj¹ jedynie na char [], wiêc nie przeœlemy struktury
	t - trafiony
	p - pudlo
	z - zatopiony
	n - niezatopiony
	l - przegrana - wysylana przez gracza, jesli juz nie ma zadnych statkow
	kto == 0 - strzela gracz 1 - losowane wy¿ej
	kto == 1 - strzela gracz 2 -     - || -
	
	*/



	char szMessage[] = "t";
	char szMessage2[] = "p";
	if (kto == 0){
		send(Socket, szMessage, 1, 0);
		send(Socket2, szMessage2, 1, 0);
	}
	else{
		send(Socket, szMessage2, 1, 0);
		send(Socket2, szMessage, 1, 0);

	}
	while (kto<2){
		if (kto == 0){
		//	std::cout << "pierwszy recv 1" << std::endl;
			recv(Socket, szMessage, 1, 0);
		//	std::cout << "drugi recv 1" << std::endl;
			recv(Socket, szMessage2, 1, 0);
		//	std::cout << "pierwszy send 2" << std::endl;
			send(Socket2, szMessage, 1, 0);
		//	std::cout << "drugi send 2" << std::endl;
			send(Socket2, szMessage2, 1, 0);
		//	std::cout << "pierwszy recv 2" << std::endl;
			recv(Socket2, szMessage, 1, 0);
		//	std::cout << "drugi recv 2" << std::endl;
			recv(Socket2, szMessage2, 1, 0);
		//	std::cout << "pierwszy send 1" << std::endl;
			send(Socket, szMessage, 1, 0);
		//	std::cout << "drugi send 1" << std::endl;
			send(Socket, szMessage2, 1, 0);
		//	std::cout << "koniec" << std::endl;
			std::cout << szMessage[0];
			if (szMessage[0] == 't')
				kto = 0;
			else
				kto = 1;
		}
		else 
			if (kto == 1){
			//	std::cout << "kurde" << std::endl;
			//	std::cout << "pierwszy recv 1" << std::endl;
				recv(Socket2, szMessage, 1, 0);
			//	std::cout << "drugi recv 1" << std::endl;
				recv(Socket2, szMessage2, 1, 0);
			//	std::cout << "pierwszy send 2" << std::endl;
				send(Socket, szMessage, 1, 0);
			//	std::cout << "drugi send 2" << std::endl;
				send(Socket, szMessage2, 1, 0);
			//	std::cout << "pierwszy recv 2" << std::endl;
				recv(Socket, szMessage, 1, 0);
			//	std::cout << "drugi recv 2" << std::endl;
				recv(Socket, szMessage2, 1, 0);
			//	std::cout << "pierwszy send 1" << std::endl;
				send(Socket2, szMessage, 1, 0);
			//	std::cout << "drugi send 1" << std::endl;
				send(Socket2, szMessage2, 1, 0);
			//	std::cout << "koniec" << std::endl;
			//	std::cout << szMessage[0];
				if (szMessage[0] == 't')
					kto = 1;
				else
					kto = 0;
			}
		
	}
	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	shutdown(Socket2, SD_SEND);
	closesocket(Socket2);
	WSACleanup();
	system("PAUSE");
	return 0;
}


/*#include <windows.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h> // _beginthread() 

#define PORT    "32001" //Port do nasluchu 
#define BACKLOG 10      // Maxksymalnie klientow do polaczenia wysylane do listen() 

void handle(void *pParam)
{
	// send(), recv(), closesocket() 
}

int main(void)
{
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	int iResult;
	SOCKET sock;
	struct addrinfo hints, *res;
	int reuseaddr = 1; // True 

	// Start Winsock 
	if ((iResult = WSAStartup(wVersion, &wsaData)) != 0) {
		printf("WSAStartup blad: %d\n", iResult);
		return 1;
	}

	// Pobieranie addrinfo 
	ZeroMemory(&hints, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(NULL, PORT, &hints, &res) != 0) {
		perror("getaddrinfo");
		return 1;
	}

	//  Tworzenie socketa 
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == INVALID_SOCKET) {
		perror("socket");
		WSACleanup();
		return 1;
	}
	// Sprawadzanie czy mozna ponownie uzyc socketu 

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuseaddr,
		sizeof(int)) == SOCKET_ERROR) {
		perror("setsockopt");
		WSACleanup();
		return 1;
	}
	// Bind adresu 

	if (bind(sock, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR) {
		perror("bind");
		WSACleanup();
		return 1;
	}

	freeaddrinfo(res);

	// Nasluch (listen()) 
	if (listen(sock, BACKLOG) == SOCKET_ERROR) {
		perror("listen");
		WSACleanup();
		return 1;
	}


	while (1) {
		size_t size = sizeof(struct sockaddr);
		struct sockaddr_in their_addr;
		SOCKET newsock;

		ZeroMemory(&their_addr, sizeof (struct sockaddr));
		newsock = accept(sock, (struct sockaddr*)&their_addr, &size);
		if (newsock == INVALID_SOCKET) {
			perror("accept\n");
		}
		else {
			// W przeciwnym wypadku uzyj nowego socketa
			uintptr_t thread;
			printf("Otrzymuje polaczenie od %s na porcie nr. %d\n",
				inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port));
			printf("Nowy socket to %d\n", newsock);
			thread = _beginthread(handle, 0, &newsock);
			if (thread == -1) {
				fprintf(stderr, "Blad tworzenia watku: %d\n", GetLastError());
				closesocket(newsock);
			}
		}
	}

	// Czyszczenie 
	closesocket(sock);
	WSACleanup();

	return 0;
}
*/