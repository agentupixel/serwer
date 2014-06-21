#include "Serwer.h"

using namespace std;

struct sockets{
	SOCKET socket;
	SOCKET temp;
	SOCKET temp2;
}s;

Serwer::Serwer() throw(string)
{
	port = 27015;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat)){
		string exception = "WSA initialization failure";
		throw exception;
	}

	if ((Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
		string exception = "socket creation failure";
		throw exception;
	}

	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(port);

	DWORD dwRecvfromTimeout = 1000;

	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR){
		string exception = "socket bind failure";
		throw exception;
	}
}

Serwer::~Serwer()
{
	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	WSACleanup();
}

void handle(void * u){
	cout << "creating thread..." << endl;
	srand(static_cast<unsigned int>(time(0)));
	int who = rand() % 2;
	SOCKET Socket2 = s.temp2;
	SOCKET TempSock = s.temp;
	char szMessage[] = "t";
	char szMessage2[] = "p";

	if (who == 0){
		send(TempSock, szMessage, 1, 0);
		send(Socket2, szMessage2, 1, 0);
	}
	else{
		send(TempSock, szMessage2, 1, 0);
		send(Socket2, szMessage, 1, 0);
	}

	do{
		if (who == 0){
			recv(TempSock, szMessage, 1, 0);
			recv(TempSock, szMessage2, 1, 0);
			send(Socket2, szMessage, 1, 0);
			send(Socket2, szMessage2, 1, 0);
			recv(Socket2, szMessage, 1, 0);
			recv(Socket2, szMessage2, 1, 0);
			send(TempSock, szMessage, 1, 0);
			send(TempSock, szMessage2, 1, 0);
			if (szMessage[0] == 't')
				who = 0;
			else
				who = 1;
		}
		else
			if (who == 1){
				recv(Socket2, szMessage, 1, 0);
				recv(Socket2, szMessage2, 1, 0);
				send(TempSock, szMessage, 1, 0);
				send(TempSock, szMessage2, 1, 0);
				recv(TempSock, szMessage, 1, 0);
				recv(TempSock, szMessage2, 1, 0);
				send(Socket2, szMessage, 1, 0);
				send(Socket2, szMessage2, 1, 0);
				if (szMessage[0] == 't')
					who = 1;
				else
					who = 0;
			}
	} while (szMessage[0] != 'l');

	closesocket(Socket2);
	closesocket(TempSock);
}

void Serwer::connection(){

	listen(Socket, SOMAXCONN);
	cout << SOMAXCONN << endl;

	while (true){
		SOCKET Sock = SOCKET_ERROR;
		SOCKET Sock2 = SOCKET_ERROR;
		ZeroMemory(&serverInf, sizeof (struct sockaddr));

		while (Sock == static_cast<unsigned int>(SOCKET_ERROR))
			Sock = accept(Socket, NULL, NULL);
		
		while (Sock2 == static_cast<unsigned int>(SOCKET_ERROR))
			Sock2 = accept(Socket, NULL, NULL);
		
		if (Sock != static_cast<unsigned int>(SOCKET_ERROR)){
			s.socket = Socket;
			s.temp = Sock;
			s.temp2 = Sock2;
			_beginthread(handle, 0, NULL);
		}
	}
}
