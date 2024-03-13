#pragma once
#include "Header.h"

class ClientSocket
{
private:
	SOCKET client_socket;
	SOCKET server_socket;

	WSADATA	wsa_data;
	sockaddr_in	addr;
public:
	ClientSocket();
	~ClientSocket();

	bool SendData(char* data);
	bool ReceiveData(char* data, int size);

	void CloseConnection();
	void ConnectToServer(char* ip_address, int port);
};

