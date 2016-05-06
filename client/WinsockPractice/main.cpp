#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "10801"

using namespace std;

void Pause(){
	cout << "Press ENTER to continue..." << endl;
	cin.sync();
	cin.ignore();
}

int __cdecl main()
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	string hostIP;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout << "WSAStartup failed with error: " << iResult << endl;
		Pause();
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	cout << "Enter the ipv4 address of the host: ";
	cin >> hostIP;

	// Resolve the server address and port
	iResult = getaddrinfo(hostIP.c_str(), DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout << "getaddrinfo failed with error: %d\n" << iResult << endl;
		WSACleanup();
		Pause();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			cout << "socket failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			Pause();
			return 1;
		}

		// Connect to server.
		cout << "Attempting to connect..." << endl;
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		cout << "Unable to connect to server!" << endl;
		WSACleanup();
		Pause();
		return 1;
	}

	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		cout << "send failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		Pause();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout << "shutdown failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		Pause();
		return 1;
	}

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			cout << "Bytes receivd: " << iResult << endl;
		else if (iResult == 0)
			cout << "Connection closed" << endl;
		else
			cout << "recv failed with error: " << WSAGetLastError() << endl;

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	Pause();
	return 0;
}
