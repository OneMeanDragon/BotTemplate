#ifndef _MMENU_H
#define _MMENU_H

#include "includes.h"

namespace Bot
{

	namespace Interface
	{

		class mMenu
		{
		private:
			static mMenu* sInstance;
			HMENU mhMenu = nullptr;
			HWND mhWnd = nullptr;

			_myMenuProc MyFileProc = NULL;
			_myMenuProc MyEditProc = NULL;

		public:
			static mMenu* Instance();
			static void Release();

			void m_hMenu(HMENU hMenu);
			HMENU m_hMenu();
			void m_hWnd(HWND hWnd);
			HWND m_hWnd();

			static BOOL WINAPI TmpOnFileProc(LPARAM lParam);
			static BOOL WINAPI TmpOnEditProc(LPARAM lParam);


		private:
			mMenu();
			~mMenu();

		};

	}

}

#endif
