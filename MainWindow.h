#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "Tray.h"


namespace Bot {

	class MainWindowC {
	private:
		static MainWindowC* sInstance;
		HICON MainIcon;
		HINSTANCE MainInstance;
		HWND MainHwnd = NULL;

		//hModule Richedit
		HINSTANCE RichEditDLL;

		BOOL mMaximized;

		Bot::Interface::TrayC* Tray = NULL;
		Bot::Interface::MainInputC* InputBox = NULL;

		wResize* MyWindows = NULL;
		Bot::Interface::wTimer* MyTimer1;


	public:
		static MainWindowC* Instance();
		static void Release();

		void hInst(const HINSTANCE hInstance);
		HINSTANCE hInst();
		void m_hWnd(const HWND hWnd);
		HWND m_hWnd();

		void Run();

		//temp timer
		static BOOL WINAPI TmpTimerProc(LPARAM lParam);

	private:
		MainWindowC();
		~MainWindowC();

		static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
		int OnInitalization(HWND hWnd);
		int OnPaint(HWND hWnd);
		int OnCTRLColor(WPARAM wParam);
		int OnTray(HWND hWnd, LPARAM lParam);
		int OnClose(HWND hWnd);
		int OnSize(HWND hWnd, WPARAM wParam);
		int OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
		int OnTimer(WPARAM wParam, LPARAM lParam);


	};

}




#endif
