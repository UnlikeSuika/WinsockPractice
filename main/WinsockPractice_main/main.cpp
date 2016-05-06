#include "ServerClass.h"

void Pause(){
	cout << "Press ENTER to continue...";
	cin.sync();
	cin.ignore();
}

int __cdecl main(){
	ServerClass sc("192.168.1.77");
	if (!sc.Initialize()){
		Pause();
		return 1;
	}
	if (!sc.ListenForSocket()){
		Pause();
		return 2;
	}
	if (!sc.AcceptSocket()){
		Pause();
		return 3;
	}
	if (!sc.Receive()){
		Pause();
		return 4;
	}
	if (!sc.Send("ORA ORA ORA")){
		Pause();
		return 5;
	}
	if (!sc.Shutdown()){
		Pause();
		return 6;
	}
	
	Pause();
	return 0;
}