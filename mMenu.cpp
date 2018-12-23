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

		mMenu::mMenu() {}

		mMenu::~mMenu() {}

		void mMenu::m_hMenu(const HMENU hMenu) {
			mhMenu = hMenu;
		}

		HMENU mMenu::m_hMenu() {
			return mhMenu;
		}
		


	}

}

