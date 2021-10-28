#pragma once
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Client
{
	public:
		Client(string _nickName);
		void Connect(string _ipAddress, int _port);
		bool isConnected();
		int sendData(string userInput);
		string getData();
		string getNickName() { return nickName; }

	private: 
		string nickName;
		SOCKET sock;
		char buf[4096];
		string ipAddress;
		int port;
		bool connStatus = false;
};

