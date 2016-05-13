#undef UNICODE

#ifndef _NETWORK_CLASS_H_
#define _NETWORK_CLASS_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#ifndef DEFAULT_BUFLEN
#define DEFAULT_BUFLEN 512
#endif

#ifndef DEFAULT_PORT
#define DEFAULT_PORT "10801"
#endif

using namespace std;

class NetworkClass{

public:
	NetworkClass(string ip, string port = DEFAULT_PORT, int buflen = DEFAULT_BUFLEN);
	NetworkClass(const NetworkClass& other);
	~NetworkClass();

	virtual bool Initialize();
	virtual bool Shutdown();
	bool Send(SOCKET sock, char* msg);
	bool Receive(SOCKET sock);

protected:
	string ip, port;
	int buflen;
	struct addrinfo hints;
	struct addrinfo* result;
	bool isWinsockInit;

	bool InitWinsock();
	bool ResolveServerAddPort(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult);
};


#endif