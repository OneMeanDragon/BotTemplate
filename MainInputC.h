#ifndef _MAININPUTC_H
#define _MAININPUTC_H

#include "includes.h"

namespace Bot
{
	namespace Interface {

		class MainInputC
		{
		private:
			static MainInputC* sInstance;
			HWND MainHwnd = NULL;
			WNDPROC EditBoxOldWndProc = NULL;

		public:
			static MainInputC* Instance();
			static void Release();

			void m_hWnd(const HWND hWnd);
			HWND m_hWnd();

			void InitSubclass();
			void KillSubclass();

			static LRESULT CALLBACK EditBoxSubclass(HWND EditBox, UINT uMsg, WPARAM wParam, LPARAM lParam);

		private:
			MainInputC();
			~MainInputC();

		};

		namespace InputBox
		{

			void SetText(HWND hWnd, char *text);
			void GetText(HWND hWnd, char *text);
			void AppendText(HWND hWnd, char *text);

		}

	}
}



#endif
