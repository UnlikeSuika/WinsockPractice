#include "ServerClass.h"
#include "ClientClass.h"

void Pause(){
	cout << "Press ENTER to continue...";
	cin.sync();
	cin.ignore();
}

int __cdecl main(){
	
	Pause();
	return 0;
}