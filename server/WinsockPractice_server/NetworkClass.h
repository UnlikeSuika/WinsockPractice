#ifndef _NETWORK_CLASS_H_
#define _NETWORK_CLASS_H_

#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "10801"

using namespace std;

class NetworkClass{
	string ip;
	int buflen;
public:
	NetworkClass();
	NetworkClass(const NetworkClass& other);
	~NetworkClass();
};

#endif