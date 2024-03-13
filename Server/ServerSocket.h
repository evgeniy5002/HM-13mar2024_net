#pragma once
#include "Header.h"
const int MAXSTRLEN = 255;

class ServerSocket 
{
private:
	WSADATA wsa_data;
	SOCKET client_socket;
	SOCKET server_socket;
	sockaddr_in addr;

public:
	ServerSocket();
	~ServerSocket();

	void Bind(int port);
	void Listen();
	bool SendData(char*);
	bool ReceiveData(char*, int);
	void StartHosting(int port);
	void CloseConnection(); 
	void SendDataMessage();
};