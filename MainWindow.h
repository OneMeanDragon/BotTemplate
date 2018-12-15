#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "includes.h"

namespace Bot {

	class MainWindowC {
	private:
		static MainWindowC* sInstance;
		HINSTANCE MainInstance;
		HWND MainHwnd;
	public:
		static MainWindowC* Instance();
		static void Release();

		void hInst(const HINSTANCE hInstance);
		HINSTANCE hInst();
		void m_hWnd(const HWND hWnd);
		HWND m_hWnd();

		void Run();

	private:
		MainWindowC();
		~MainWindowC();

		static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		int OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
		int OnInitalization(HWND hWnd);
		int OnPaint(HWND hWnd);
		int OnClose(HWND hWnd);
		int OnSize(HWND hWnd, WPARAM wParam);
		int OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
	};

}




#endif