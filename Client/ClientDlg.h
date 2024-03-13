#pragma once
#include "Header.h"

struct ClientDlg
{
	static ClientDlg* dlg_ptr;
	ClientDlg();

	static BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	VOID OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify);
	VOID OnClose(HWND hwnd);


};

