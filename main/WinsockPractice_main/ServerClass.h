#ifndef _SERVER_CLASS_H_
#define _SERVER_CLASS_H_

#include "NetworkClass.h"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

class ServerClass :public NetworkClass{

public:
	ServerClass(string ip, string port = DEFAULT_PORT, int buflen = DEFAULT_BUFLEN) : NetworkClass(ip,port,buflen),
		ListenSocket(INVALID_SOCKET), ClientSocket(INVALID_SOCKET){}

	bool Initialize();
	bool ListenForSocket();
	bool AcceptSocket();
	bool Shutdown();
	bool Send(char* msg);
	bool Receive();

private:
	SOCKET ListenSocket;
	SOCKET ClientSocket;

	bool CreateListenSocket();
	bool BindListenSocket();
};

#endif