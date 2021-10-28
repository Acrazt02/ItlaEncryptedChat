#include "Client.h"

Client::Client(string _nickName) {
	
	if (_nickName.size() > 0) {
		nickName = _nickName;
	}
	else {
		nickName = "Unknown";
	}
}

void Client::Connect(string _ipAddress, int _port) {
	
	ipAddress = _ipAddress;
	port = _port;

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		connStatus = false;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		connStatus = false;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		connStatus = false;
		return;
	}

	connStatus = true;
}

bool Client::isConnected() {
	return connStatus;
}

int Client::sendData(string userInput) {

	if (userInput.size() > 0 && connStatus)		// Make sure the user has typed in something
	{
		userInput = userInput;

		// Send the text
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		if (sendResult != SOCKET_ERROR)
		{
			return 0; //Data send successfully
		}
		else {
			return -1;
		}
	}
}

string Client::getData() {

	if (connStatus) // Make sure the user has typed in something 
	{
		// Wait for response
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		if (bytesReceived > 0)
		{
			return string(buf, 0, bytesReceived);
		}
		else {
			return "";
		}
	}

}
