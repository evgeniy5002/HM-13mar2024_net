#include "Header.h"
#include "ServerSocket.h"

ServerSocket::ServerSocket()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != NO_ERROR)
	{
		cout << "WSAStartup error\n";
		system("pause");
		WSACleanup();
		exit(10);
	}

	client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client_socket == INVALID_SOCKET)
	{
		cout << "Socket create error." << endl;
		system("pause");
		WSACleanup();
		exit(11);
	}
}

ServerSocket::~ServerSocket()
{
	WSACleanup();
}

bool ServerSocket::SendData(char *buffer)
{
	send(client_socket, buffer, strlen(buffer), 0);
	return true;
}

bool ServerSocket::ReceiveData(char *buffer, int size)
{
	int i = recv(client_socket, buffer, size, 0);
	buffer[i] = '\0';
	return (i > 0);
}

void ServerSocket::CloseConnection()
{
	closesocket(client_socket);
}

void ServerSocket::SendDataMessage()
{
	char message[MAXSTRLEN];
	cin.ignore();
	cout << "Input message: ";
	cin.get(message, MAXSTRLEN);
	SendData(message);
}

void ServerSocket::StartHosting(int port)
{
	Bind(port);
	Listen();
}

void ServerSocket::Listen()
{
	cout << "Waiting for client..." << endl;

	if (listen(client_socket, 1) == SOCKET_ERROR)
	{
		cout << "Listening error\n";
		system("pause");
		WSACleanup();
		exit(15);
	}

	server_socket = accept(client_socket, NULL, NULL);
	while (server_socket == SOCKET_ERROR)
	{
		server_socket = accept(client_socket, NULL, NULL);
	}
	client_socket = server_socket;
}

void ServerSocket::Bind(int port)
{
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
	addr.sin_port = htons(port);
	cout << "Binding to port:  " << port << endl;
	if (bind(client_socket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		cout << "Failed to bind to port\n";
		system("pause");
		WSACleanup();
		exit(14);
	}
}