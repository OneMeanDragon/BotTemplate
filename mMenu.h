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
			HMENU mhMenu;

		public:
			static mMenu* Instance();
			void Release();

			void m_hMenu(const HMENU hMenu);
			HMENU m_hMenu();

		private:
			mMenu();
			~mMenu();

		};

	}

}

#endif
