#ifndef _CLIENT_CLASS_H_
#define _CLIENT_CLASS_H_

#include "NetworkClass.h"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

class ClientClass :public NetworkClass{

public:
	ClientClass(string ip, string port = DEFAULT_PORT, int buflen = DEFAULT_BUFLEN) : NetworkClass(ip, port, buflen),
		ConnectSocket(INVALID_SOCKET), ptr(NULL){}

	bool Initialize();
	bool Shutdown();
	bool Send(char* msg);
	bool Receive();

private:
	SOCKET ConnectSocket;
	struct addrinfo* ptr;
};

#endif