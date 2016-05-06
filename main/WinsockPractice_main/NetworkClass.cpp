#include "NetworkClass.h"

//NetworkClass constructor
NetworkClass::NetworkClass(string ip, string port, int buflen){
	this->ip = ip;
	this->port = port;
	this->buflen = buflen;
	result = NULL;
	isWinsockInit = false;
}

//Do not use this constructor
NetworkClass::NetworkClass(const NetworkClass& other){}

//Do not use this destructor
NetworkClass::~NetworkClass(){}

//Initializes NetworkClass object, returns true when successfully initialized
bool NetworkClass::Initialize(){
	return true;
}

//Shuts down NetworkClass object, returns true when successfully shut down
bool NetworkClass::Shutdown(){
	return true;
}

//Initialize Winsock
bool NetworkClass::InitWinsock(){
	if (!isWinsockInit){
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult){
			cout << "WSAStartup failed with error: " << iResult << endl;
			return false;
		}
		isWinsockInit = true;
	}
	return true;
}

//Resolve the server address and port
bool NetworkClass::ResolveServerAddPort(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA *pHints, PADDRINFOA *ppResult){
	int iResult = getaddrinfo(pNodeName, pServiceName, pHints, ppResult);
	if (iResult){
		cout << "getaddrinfo failed with error: " << iResult << endl;
		WSACleanup();
		return false;
	}
	return true;
}