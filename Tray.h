#ifndef _TRAY_H
#define _TRAY_H

#include "includes.h"

namespace Bot
{
	namespace Interface {

		class TrayC {
		private:
			static TrayC* sInstance;
			BOOL mTrayed;
		public:
			static TrayC* Instance();
			static void Release();

			void Add(HWND hWnd);
			void Remove(HWND hWnd);

			void Restore(HWND hWnd, BOOL IS_MAX);

			BOOL InTray();

		private:
			TrayC();
			~TrayC();
		};

	}
}
#endif
