#include <iostream>
#include <winsock2.h>
#include <ctime>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	srand(time(0));
	int kto = rand() % 2;

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

	char szMessage[] = "p";
	char szMessage2[] = "n";
	if (kto){
		send(Socket, "t", strlen(szMessage), 0);
		send(Socket, "n", strlen(szMessage2), 0);
		send(Socket2, "p", strlen(szMessage), 0);
		send(Socket2, "n", strlen(szMessage2), 0);
	}
	else{
		send(Socket2, "t", strlen(szMessage), 0);
		send(Socket2, "n", strlen(szMessage2), 0);
		send(Socket, "p", strlen(szMessage), 0);
		send(Socket, "n", strlen(szMessage2), 0);
	}
	/*while (true){
	  pêtla g³ówna
	}*/
	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	shutdown(Socket2, SD_SEND);
	closesocket(Socket2);
	WSACleanup();
	system("PAUSE");
	return 0;
}