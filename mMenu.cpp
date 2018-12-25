#include "mMenu.h"

namespace Common
{

	void InsertPopMenu(HMENU hMenu, UINT pos, _myMenuProc pFunc, LPCSTR strMenuName)
	{
		InsertMenu(hMenu, pos, MF_STRING | MF_POPUP, (UINT_PTR)(pFunc), strMenuName);
	}


	void AddMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName)
	{
		AppendMenu(hMenu, MF_STRING, (UINT_PTR)(pFunc), strMenuName);
	}

	void AddPopMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName)
	{
		AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)(pFunc), strMenuName);
	}

	void AddSubMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName, LPCSTR strSubMenuName)
	{
		HMENU MenuTitle = FindMenu(hMenu, strMenuName);

		AddMenu(MenuTitle, pFunc, strSubMenuName);
	}

	void AddSubMenuSubMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMainName, LPCSTR strSubMainName, LPCSTR strSubName)
	{
		HMENU MainTitle = FindMenu(hMenu, strMainName);
		HMENU SubMainTitle = FindMenu(MainTitle, strSubMainName);
		AddMenu(SubMainTitle, pFunc, strSubName);
	}

	void AddSubPopMenu(HMENU hMenu, _myMenuProc pFunc, LPCSTR strMenuName, LPCSTR strSubMenuName)
	{
		HMENU MenuTitle_SubMenu = FindMenu(hMenu, strMenuName);
		HMENU hSubPop = CreatePopupMenu();
		InsertMenu(MenuTitle_SubMenu, 0, MF_POPUP, (UINT_PTR)hSubPop, strSubMenuName);
	}

	HMENU FindMenu(const HMENU hMainMenu, const LPCSTR byName)
	{
		UINT MenuItems = GetMenuItemCount(hMainMenu);

		for (UINT i = 0; i < MenuItems; i++) {
			int MenuStringSize;
			LPSTR MenuString = new CHAR[MenuStringSize = GetMenuString(hMainMenu, i, 0, 0, MF_BYPOSITION) + 1];
			if (GetMenuString(hMainMenu, i, MenuString, MenuStringSize, MF_BYPOSITION)
				&& !strcmp(MenuString, byName)) {
				delete[] MenuString;
				return GetSubMenu(hMainMenu, i);
			}

			delete[] MenuString;
		}

		// Menu not found, create it

		HMENU PopupMenu = CreateMenu();

		AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)PopupMenu, byName);

		return PopupMenu;
	}

}

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
			MyFileExitProc = TmpOnFileExitProc;
			MyEditProc = TmpOnEditProc;
		}

		mMenu::~mMenu() {}

		void mMenu::m_hWnd(HWND hWnd) {
			mhWnd = hWnd;
			//if hwnd != null blah blah
			if (SetMenu(m_hWnd(), m_hMenu())) {
				//Add File
				HMENU hFilePopup = CreatePopupMenu();
				InsertMenu(m_hMenu(), 0, MF_POPUP, (UINT_PTR)hFilePopup, "&File");
				Common::AddSubMenu(m_hMenu(), MyFileExitProc, "&File", "E&xit");

				//Add Edit
				HMENU hEditPopup = CreatePopupMenu();
				InsertMenu(m_hMenu(), 1, MF_POPUP, (UINT_PTR)hEditPopup, "&EditTmp");
				Common::AddSubPopMenu(m_hMenu(), MyEditProc, "&EditTmp", "ZEdit");
				Common::AddSubMenuSubMenu(m_hMenu(), MyFileProc, "&EditTmp", "ZEdit", "Bob");

				DrawMenuBar(m_hWnd());
			}
		}

		BOOL WINAPI mMenu::TmpOnEditProc(LPARAM lParam) {
			OutputDebugString("You have clicked EDIT in the menu.\r\n\r\n");

			return TRUE;
		}

		BOOL WINAPI mMenu::TmpOnFileExitProc(LPARAM lParam) {
			OutputDebugString("You have clicked EXIT in the menu.\r\n\r\n");

			return TRUE;
		}

		BOOL WINAPI mMenu::TmpOnFileProc(LPARAM lParam) {
			OutputDebugString("You have clicked Bob in the menu.\r\n\r\n");

			return FALSE;
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

