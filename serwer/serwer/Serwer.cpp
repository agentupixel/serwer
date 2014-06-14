#include "Serwer.h"

using namespace std;

struct sockety{
	SOCKET socket;
	SOCKET temp;
	SOCKET temp2;
}s;

Serwer::Serwer() throw(string)
{
	port = 27015;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat)){
		string wyjatek = "WSA Initialization failure";
		throw wyjatek;
	}

	if ((Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
		string wyjatek = "Socket creation failure";
		throw wyjatek;
	}

	serverInf.sin_family = AF_INET;
	serverInf.sin_addr.s_addr = INADDR_ANY;
	serverInf.sin_port = htons(port);

	if (bind(Socket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR){
		string wyjatek = "Socket bind failure";
		throw wyjatek;
	}


}

Serwer::~Serwer()
{
	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	WSACleanup();
}

void handle(void * u){
	cout << "tworze watek!" << endl;
	srand(static_cast<unsigned int>(time(0)));
	int kto = rand() % 2;
	SOCKET Socket2 = s.temp2;
	SOCKET TempSock = s.temp;
	char szMessage[] = "t";
	char szMessage2[] = "p";

	if (kto == 0){
		send(TempSock, szMessage, 1, 0);
		send(Socket2, szMessage2, 1, 0);
	}
	else{
		send(TempSock, szMessage2, 1, 0);
		send(Socket2, szMessage, 1, 0);
	}

	while (szMessage[0] != 'l'){
		if (kto == 0){
			recv(TempSock, szMessage, 1, 0);
			recv(TempSock, szMessage2, 1, 0);
			send(Socket2, szMessage, 1, 0);
			send(Socket2, szMessage2, 1, 0);
			recv(Socket2, szMessage, 1, 0);
			recv(Socket2, szMessage2, 1, 0);
			send(TempSock, szMessage, 1, 0);
			send(TempSock, szMessage2, 1, 0);
			if (szMessage[0] == 't')
				kto = 0;
			else
				kto = 1;
		}
		else
			if (kto == 1){
				recv(Socket2, szMessage, 1, 0);
				recv(Socket2, szMessage2, 1, 0);
				send(TempSock, szMessage, 1, 0);
				send(TempSock, szMessage2, 1, 0);
				recv(TempSock, szMessage, 1, 0);
				recv(TempSock, szMessage2, 1, 0);
				send(Socket2, szMessage, 1, 0);
				send(Socket2, szMessage2, 1, 0);
				if (szMessage[0] == 't')
					kto = 1;
				else
					kto = 0;
			}
	}
	closesocket(Socket2);
	closesocket(TempSock);
	//koment
}

void Serwer::connection(){

	listen(Socket, SOMAXCONN);
	cout << SOMAXCONN << endl;

	while (true){
		SOCKET Sock = SOCKET_ERROR;
		SOCKET Sock2 = SOCKET_ERROR;
		ZeroMemory(&serverInf, sizeof (struct sockaddr));

		while (Sock == static_cast<unsigned int>(SOCKET_ERROR)){
			cout << "czekam na klienta1\r";
			Sock = accept(Socket, NULL, NULL);
		}

		cout << endl << "1 podlaczony" << endl;

		while (Sock2 == static_cast<unsigned int>(SOCKET_ERROR)){
			cout << "czekam na klienta2\r";
			Sock2 = accept(Socket, NULL, NULL);
		}

		cout << endl << "juz nie czekam" << endl;
		if (Sock != static_cast<unsigned int>(SOCKET_ERROR)){
			s.socket = Socket;
			s.temp = Sock;
			s.temp2 = Sock2;
			_beginthread(handle, 0, NULL);
		}
	}
}

/*
send i recv operuj� jedynie na char [], wi�c nie prze�lemy struktury
t - trafiony
p - pudlo
z - zatopiony
n - niezatopiony
l - przegrana - wysylana przez gracza, jesli juz nie ma zadnych statkow
kto == 0 - strzela gracz 1 - losowane wy�ej
kto == 1 - strzela gracz 2 -     - || -

*/
