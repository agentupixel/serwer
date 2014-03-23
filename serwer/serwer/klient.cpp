/* trzeba to skompilowac w osobnym projekcie i wtedy mo¿na testowaæ dzia³¹nie i dopisywaæ jakieœ œcierwa*/
/*
#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int convert(char sign){
int x = static_cast<int>(sign);
return x;
}


void clear_buffer(char buffer[], int i){
for (int k = 0; k < i; k++)
buffer[k] = 0;
}

int main(){

//int x, y, m;
WSADATA WsaDat;
if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0){
std::cout << "Winsock error - Winsock initialization failed\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (Socket == INVALID_SOCKET){
std::cout << "Winsock error - Socket creation Failed!\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

struct hostent *host;
if ((host = gethostbyname("localhost")) == NULL){
std::cout << "Failed to resolve hostname.\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

SOCKADDR_IN SockAddr;
SockAddr.sin_port = htons(27015);
SockAddr.sin_family = AF_INET;
SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
std::cout << "Failed to establish connection with server\r\n";
WSACleanup();
system("PAUSE");
return 0;
}


char buffer[1], tempBuffer[1];
memset(buffer, 0, 1);
memset(tempBuffer, 0, 1);
recv(Socket, buffer, 1, 0);
tempBuffer[0] = buffer[0];
if (tempBuffer[0] == 't')
std::cout << "set target" << std::endl;
else
std::cout << "opponent is shooting" << std::endl;
recv(Socket, buffer, 1, 0);

clear_buffer(buffer, 1);

std::cout << std::endl;
shutdown(Socket, SD_SEND);

closesocket(Socket);

WSACleanup();
system("PAUSE");
return 0;
}*/