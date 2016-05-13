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

//Initializes NetworkClass object, virtual
bool NetworkClass::Initialize(){
	return true;
}

//Shuts down NetworkClass object, virtual
bool NetworkClass::Shutdown(){
	return true;
}

//Sends message to the given socket
bool NetworkClass::Send(SOCKET sock, char* msg){
	int iSendResult = send(sock, msg, strlen(msg), 0);
	if (iSendResult == SOCKET_ERROR){
		cout << "send failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	cout << "Bytes sent: " << iSendResult << endl;
	return true;
}

//Receives message from the given socket
bool NetworkClass::Receive(SOCKET sock){
	char msg[DEFAULT_BUFLEN];
	int iResult = recv(sock, msg, buflen, 0);
	if (iResult > 0){
		cout << "Bytes received: " << iResult << endl;
		cout << "Message received: " << msg << endl;
		return true;
	}
	else if (iResult == 0){
		cout << "Connection closing..." << endl;
		return false;
	}
	else{
		cout << "recv failed with error: " << WSAGetLastError() << endl;
		return false;
	}
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