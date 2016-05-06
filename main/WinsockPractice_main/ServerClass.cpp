#include "ServerClass.h"

bool ServerClass::Initialize(){

	if (!InitWinsock()){
		return false;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (!ResolveServerAddPort(NULL, port.c_str(), &hints, &result)){
		return false;
	}

	if (!CreateListenSocket()){
		return false;
	}

	if (!BindListenSocket()){
		return false;
	}

	freeaddrinfo(result);
	return true;
}

//Listen for incoming SOCKET
bool ServerClass::ListenForSocket(){
	cout << "Listening for socket..." << endl;
	if ((listen(ListenSocket, SOMAXCONN)) == SOCKET_ERROR){
		cout << "listen failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Accept a client socket
bool ServerClass::AcceptSocket(){
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET){
		cout << "accept failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Shuts down the ServerClass object
bool ServerClass::Shutdown(){
	if (shutdown(ClientSocket, SD_SEND) == SOCKET_ERROR) {
		cout << "shutdown failed with error: " << WSAGetLastError() << endl;
		closesocket(ClientSocket);
		WSACleanup();
		return false;
	}
	if (closesocket(ListenSocket)){
		cout << "closesocket failed with error: " << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	WSACleanup();
	return true;
}

//Send message to client
bool ServerClass::Send(char* msg){
	int iSendResult = send(ClientSocket, msg, strlen(msg), 0);
	if (iSendResult == SOCKET_ERROR){
		cout << "send failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Receive message from client, returns true if message is received and client is still connected
bool ServerClass::Receive(){
	char msg[DEFAULT_BUFLEN];
	int iResult = recv(ClientSocket, msg, buflen, 0);
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

//Create a SOCKET for connecting to server
bool ServerClass::CreateListenSocket(){
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET){
		cout << "socket failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}

//Setup the TCP listening socket
bool ServerClass::BindListenSocket(){
	int iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR){
		cout << "bind failed with error: " << WSAGetLastError() << endl;
		return false;
	}
	return true;
}