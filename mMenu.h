#ifndef _MMENU_H
#define _MMENU_H

#include "includes.h"

namespace Common
{

	void InsertPopMenu(HMENU hMenu, UINT pos, _myMenuProc pFunc, LPCSTR strMenuName);
	void AddMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName);
	void AddPopMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName);
	void AddSubMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName, LPCSTR strSubMenuName);
	void AddSubMenuSubMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMainName, LPCSTR strSubMainName, LPCSTR strSubName);
	void AddSubPopMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName, LPCSTR strSubMenuName);
	HMENU FindMenu(const HMENU hMainMenu, const LPCSTR byName);


}

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
			_myMenuProc MyFileExitProc = NULL;
			_myMenuProc MyEditProc = NULL;

		public:
			static mMenu* Instance();
			static void Release();

			void m_hMenu(HMENU hMenu);
			HMENU m_hMenu();
			void m_hWnd(HWND hWnd);
			HWND m_hWnd();

			static BOOL WINAPI TmpOnFileProc(LPARAM lParam);
			static BOOL WINAPI TmpOnFileExitProc(LPARAM lParam);
			static BOOL WINAPI TmpOnEditProc(LPARAM lParam);


		private:
			mMenu();
			~mMenu();

		};

	}

}

#endif
