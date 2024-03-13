#include <iostream>
#include "ServerSocket.h"
using namespace std;

int main()
{
	int nChoice;
	int port = 3000; //выбираем порт
	string ipAddress; //Адрес сервера
	char receiveMessage[MAXSTRLEN];
	char sendMessage[MAXSTRLEN];
	cout << "1) Start server" << endl;
	cout << "3) Exit" << endl;
	cin >> nChoice;
	if (nChoice == 1)
	{
		ServerSocket server;
		cout << "Starting server..." << endl;
	
		server.StartHosting(port);

		while (true)
		{
			cout << "\tWaiting..." << endl;
			
			if (server.ReceiveData(receiveMessage, MAXSTRLEN)) {
				cout << "Received: " << receiveMessage << endl;

				if (strcmp(receiveMessage, "end") == 0 || strcmp(sendMessage, "end") == 0) {
					break;
				}

				server.SendDataMessage();
			}
			else {
				cout << "Failed" << endl;
				server.CloseConnection();
				break;
			}
		}

		server.CloseConnection();
	}
	else if (nChoice == 3)
		return 0;
}


