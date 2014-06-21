#ifndef SERWER_H_INCLUDED
#define SERWER_H_INCLUDED

#include <iostream>
#include <ctime>
#include <string>
#include <winsock2.h>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")

class Serwer
{
public:
	Serwer() throw(std::string);
	~Serwer();
	void connection();
	friend void handle(void *);

private:
	WSADATA WsaDat;
	SOCKET Socket;
	SOCKADDR_IN serverInf;
	int port;
};


#endif // SERWER_H_INCLUDED
