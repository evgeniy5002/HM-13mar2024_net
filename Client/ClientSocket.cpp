#include "ClientSocket.h"

ClientSocket::ClientSocket() {

	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != NO_ERROR) {
		system("pause");
		WSACleanup();
		exit(10);
	}

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client_socket == INVALID_SOCKET) {
		system("pause");
		WSACleanup();
		exit(10);
	}
}

ClientSocket::~ClientSocket() {
	WSACleanup();
}

void ClientSocket::ConnectToServer(char* ip_address, int port) {
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip_address, &addr.sin_addr);
	addr.sin_port = htons(port);

	if (connect(client_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, L"Connection error", NULL, MB_OK);
		/*system("pause");*/
		WSACleanup();
		exit(13);
	}
}

bool ClientSocket::SendData(char* data) {
	send(client_socket, data, strlen(data), 0);
	return true;
}

bool ClientSocket::ReceiveData(char* data, int size) {
	int i = recv(client_socket, data, size, 0);
	data[i] = '\0';
	return (i > 0);
}

void ClientSocket::CloseConnection()
{
	closesocket(client_socket);
}