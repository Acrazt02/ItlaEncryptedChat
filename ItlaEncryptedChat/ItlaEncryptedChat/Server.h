#pragma once
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <map>

#include "MessageEncryptor.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

class Server
{
public:
	Server();
	void Start();
	void Listen();
	void BroadCast();
	void Close();
private:
	SOCKET listening;
	fd_set master;
	int port = 10500;
	bool isRunning = false;
	//int colors[15] = { 40,41,42,43,44,45,46,47 };
};

