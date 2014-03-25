/* trzeba to skompilowac w osobnym projekcie i wtedy mo¿na testowaæ dzia³¹nie i dopisywaæ funkcje*/
/*

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int toint(char sign[]){
int x = static_cast<int>(sign[0]);
return x;
}

char tochar(int sign){
char x;
x = static_cast<char>(sign);
return x;
}

int main()
{

int x = 1, y = 2, m;
// Initialise Winsock
WSADATA WsaDat;
if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
{
std::cout << "Winsock error - Winsock initialization failed\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

// Create our socket
SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (Socket == INVALID_SOCKET)
{
std::cout << "Winsock error - Socket creation Failed!\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

// Resolve IP address for hostname
struct hostent *host;
if ((host = gethostbyname("localhost")) == NULL)
{
std::cout << "Failed to resolve hostname.\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

// Setup our socket address structure
SOCKADDR_IN SockAddr;
SockAddr.sin_port = htons(27015);
SockAddr.sin_family = AF_INET;
SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

// Attempt to connect to server
if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0)
{
std::cout << "Failed to establish connection with server\r\n";
WSACleanup();
system("PAUSE");
return 0;
}

// Display message from server
char buffer[1], tempBuffer[1];
memset(buffer, 0, 1);
memset(tempBuffer, 0, 1);
recv(Socket, buffer, 1, 0);
while (buffer[0] != 'l'){
if (buffer[0] == 't'){
std::cout << "wybierz cel" << std::endl;
//todo: wywo³anie funkcji celowania, przypisanie  x i y
buffer[0] = tochar(x);
tempBuffer[0] = tochar(y);
std::cout << "pierwszys" << std::endl;
send(Socket, buffer, 1, 0);
std::cout << "drugis" << std::endl;
send(Socket, tempBuffer, 1, 0);
std::cout << "pierwszyr" << std::endl;
recv(Socket, buffer, 1, 0);
std::cout << "drugir" << std::endl;
recv(Socket, tempBuffer, 1, 0);
std::cout << "koniec" << std::endl;
if (buffer[0] == 'p')
std::cout << "pud³o!" << std::endl;
else
if (buffer[0] == 't')
std::cout << "trafiony!" << std::endl;
else
std::cout << "smieci";

//todo: wywo³anie funkcji oznaczaj¹cej na planszy trafienie lub pud³o
//na podstawie zawartoœci buffer[0]




		}
		else
			if (buffer[0] == 'p'){
				std::cout << "celuje przeciwnik" << std::endl;
				std::cout << "pierwszypr" << std::endl;
				recv(Socket, buffer, 1, 0);
				x = toint(buffer);
				std::cout << "drugipr" << std::endl;
				recv(Socket, tempBuffer, 1, 0);
				std::cout << "koniecpr" << std::endl;
				y = toint(buffer);
				//todo: sprawdzenie, czy trafi³ i odpowiednie ustawienie buffer i tempbuffer
				buffer[0] = 't';
				tempBuffer[0] = 'n';
				std::cout << "pierwszyps" << std::endl;
				send(Socket, buffer, 1, 0);
				std::cout << "drugips" << std::endl;
				send(Socket, tempBuffer, 1, 0);
				std::cout << "koniec" << std::endl;
				buffer[0] = (buffer[0] == 't') ? 'p' : 't';
				std::cout << buffer[0] << std::endl;
			}
	}


	shutdown(Socket, SD_SEND);
	closesocket(Socket);
	WSACleanup();
	system("PAUSE");
	return 0;
}




*/

/*
send i recv operuj¹ jedynie na char [], wiêc nie przeœlemy struktury
zawartoœci tempBuffer i buffer
t - trafiony
p - pudlo
z - zatpiony
n - niezatopiony
l - przegrana - wysylana przez gracza, jesli juz nie ma zadnych statkow
*/