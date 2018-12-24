#include "mMenu.h"

namespace Bot
{

	namespace Interface
	{

		mMenu* mMenu::sInstance = NULL;

		mMenu* mMenu::Instance() {
			if (sInstance == NULL)
			{
				sInstance = new mMenu();
			}
			return sInstance;
		}

		void mMenu::Release() {
			delete sInstance;
			sInstance = NULL;
		}

		mMenu::mMenu() {
			//Create our Menu handle.
			m_hMenu(CreateMenu());

			//Set menu information
			MENUINFO mi = { 0 };
			mi.cbSize = sizeof(mi);
			mi.fMask = MIM_STYLE | MIM_APPLYTOSUBMENUS; //MIM_BACKGROUND
			//mi.hbrBack = CreateSolidBrush(RGB(0,0,0)); 
			mi.dwStyle = MNS_MODELESS; // MNS_NOCHECK;
			SetMenuInfo(m_hMenu(), &mi);

			MyFileProc = TmpOnFileProc;
			MyEditProc = TmpOnEditProc;
		}

		mMenu::~mMenu() {}

		void mMenu::m_hWnd(HWND hWnd) {
			mhWnd = hWnd;
			//if hwnd != null blah blah
			if (SetMenu(m_hWnd(), m_hMenu())) {
				AppendMenu(m_hMenu(), MF_STRING, (UINT_PTR)(MyFileProc), "&File");
				AppendMenu(m_hMenu(), MF_STRING, (UINT_PTR)(MyEditProc), "&Edit");
				DrawMenuBar(m_hWnd());
			}
		}

		BOOL WINAPI mMenu::TmpOnEditProc(LPARAM lParam) {
			return TRUE;
		}

		BOOL WINAPI mMenu::TmpOnFileProc(LPARAM lParam) {
			return TRUE;
		}

		HWND mMenu::m_hWnd() {
			return mhWnd;
		}

		void mMenu::m_hMenu(HMENU hMenu) {
			mhMenu = hMenu;
		}

		HMENU mMenu::m_hMenu() {
			return mhMenu;
		}



	}

}

