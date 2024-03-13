#include "ClientDlg.h"
#include "ClientSocket.h"

ClientSocket client_socket;
char* data_from_socket;

// === === === === === === === //

DWORD WINAPI Listen_Socket(LPVOID lpParam) {
	HWND hwnd = (HWND)lpParam;
	HWND h_static = GetDlgItem(hwnd, IDC_SERVER_MSG);

	char* reveive_message = new char[512];
	
	while (true) {
		if (client_socket.ReceiveData(reveive_message, 512)) {
			SetWindowTextA(h_static, reveive_message);
		}
		else {
			SetWindowTextA(h_static, "Connection error");
			ExitThread(0);
			break;
		}
	}

	delete[] reveive_message;
	
	return 0;
}

ClientDlg* ClientDlg::dlg_ptr = nullptr;

ClientDlg::ClientDlg() {
	dlg_ptr = this;
}

BOOL CALLBACK ClientDlg::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, dlg_ptr->OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, dlg_ptr->OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, dlg_ptr->OnCommand);
	}
	return FALSE;
}


BOOL ClientDlg::OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	return TRUE;
}

VOID ClientDlg::OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify) {
	HANDLE h_listen_socket;

	switch (id) {
	case IDC_CONNECT_BTN: {
		char ip[] = "127.0.0.1";
		client_socket.ConnectToServer(ip, 3000);
		h_listen_socket = CreateThread(NULL, 0, Listen_Socket, (LPVOID)hwnd, 0, NULL);
		break;
	}
	case IDC_SEND_BTN: {
		HWND input = GetDlgItem(hwnd, IDC_INPUT_EDIT);
		int len = GetWindowTextLength(input);
		len += 1;

		char* data = new char[len + 1];

		GetWindowTextA(input, data, len);
		data[len] = '\0';
		client_socket.SendData(data);

		delete[] data;
		break;
	}
	case IDC_DISCONNECT_BTN: {
		client_socket.CloseConnection();
		//TerminateThread(h_listen_socket, 0);
		break;
	}
	}
}

VOID ClientDlg::OnClose(HWND hwnd) {
	client_socket.CloseConnection();
	EndDialog(hwnd, 0);
}