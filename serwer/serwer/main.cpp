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
			std::cout << "pierwszy recv 1" << std::endl;
			recv(Socket, szMessage, 1, 0);
			std::cout << "drugi recv 1" << std::endl;
			recv(Socket, szMessage2, 1, 0);
			std::cout << "pierwszy send 2" << std::endl;
			send(Socket2, szMessage, 1, 0);
			std::cout << "drugi send 2" << std::endl;
			send(Socket2, szMessage2, 1, 0);
			std::cout << "pierwszy recv 2" << std::endl;
			recv(Socket2, szMessage, 1, 0);
			std::cout << "drugi recv 2" << std::endl;
			recv(Socket2, szMessage2, 1, 0);
			std::cout << "pierwszy send 1" << std::endl;
			send(Socket, szMessage, 1, 0);
			std::cout << "drugi send 1" << std::endl;
			send(Socket, szMessage2, 1, 0);
			std::cout << "koniec" << std::endl;
			std::cout << szMessage[0];
			if (szMessage[0] == 't')
				kto = 0;
			else
				kto = 1;
		}
		else 
			if (kto == 1){
				std::cout << "kupa" << std::endl;
				std::cout << "pierwszy recv 1" << std::endl;
				recv(Socket2, szMessage, 1, 0);
				std::cout << "drugi recv 1" << std::endl;
				recv(Socket2, szMessage2, 1, 0);
				std::cout << "pierwszy send 2" << std::endl;
				send(Socket, szMessage, 1, 0);
				std::cout << "drugi send 2" << std::endl;
				send(Socket, szMessage2, 1, 0);
				std::cout << "pierwszy recv 2" << std::endl;
				recv(Socket, szMessage, 1, 0);
				std::cout << "drugi recv 2" << std::endl;
				recv(Socket, szMessage2, 1, 0);
				std::cout << "pierwszy send 1" << std::endl;
				send(Socket2, szMessage, 1, 0);
				std::cout << "drugi send 1" << std::endl;
				send(Socket2, szMessage2, 1, 0);
				std::cout << "koniec" << std::endl;
				std::cout << szMessage[0];
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