#include "Serwer.h"

using namespace std;

struct sockety{
	SOCKET socket;
	SOCKET temp;
}s;

Serwer::Serwer() throw(string)
{
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
	cout << "utworzony watek" << endl;
	srand(static_cast<unsigned int>(time(0)));
	int kto = rand() % 2;
	SOCKET Socket2 = SOCKET_ERROR;
	SOCKET TempSock = s.temp;
	while (Socket2 == SOCKET_ERROR){
		cout << "nie lacze\r";
		Socket2 = accept(s.socket, NULL, NULL);
	}

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
}

void Serwer::connection(){
	
	
	listen(Socket, 100);

	while (true){

		SOCKET TempSock = SOCKET_ERROR;
		ZeroMemory(&serverInf, sizeof (struct sockaddr));
		while (TempSock == SOCKET_ERROR)
			TempSock = accept(Socket, NULL, NULL);
		
		if (TempSock != SOCKET_ERROR){
			s.socket = Socket;
			s.temp = TempSock;
			_beginthread(handle, 0, NULL);
		}
	}

}

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