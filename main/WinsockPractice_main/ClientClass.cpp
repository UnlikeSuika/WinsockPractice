#include "ClientClass.h"

//Initializes ClientClass object
bool ClientClass::Initialize(){

	int iResult;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//User input for ipv4 address
	cout << "Enter the ipv4 address of the host: ";
	cin >> ip;

	if (!ResolveServerAddPort(ip.c_str(), port.c_str(), &hints, &result)){
		return false;
	}
	
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next){
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET){
			cout << "socket failed with error: " << WSAGetLastError() << endl;
		}

		//Connect to server
		cout << "Attempting to connect..." << endl;
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR){
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}

		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET){
		cout << "Unable to connect to server!" << endl;
		return false;
	}

	return true;
}

//Shuts down ClientClass object
bool ClientClass::Shutdown(){
	closesocket(ConnectSocket);
	WSACleanup();
	return true;
}

//Sends a message to the connected socket
bool ClientClass::Send(char* msg){
	return NetworkClass::Send(ConnectSocket, msg, (int)strlen(msg), 0);
}

//Receives a message from the connected socket
bool ClientClass::Receive(){
	return NetworkClass::Receive(ConnectSocket);
}