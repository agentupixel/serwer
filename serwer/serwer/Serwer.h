#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")

class Serwer
{
public:
	Serwer() throw(std::string);
	Serwer(int port) throw(std::string);
	~Serwer();
	void connection();
	friend void handle(void *);

private:
	int kto;
	WSADATA WsaDat;
	SOCKET Socket;
	SOCKADDR_IN serverInf;
	int port = 27015;
};

