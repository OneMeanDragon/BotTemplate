#include "Tray.h"
#include <string>

namespace Bot
{
	namespace Interface {

		TrayC* TrayC::sInstance = NULL;

		TrayC* TrayC::Instance() {
			if (sInstance == NULL)
			{
				sInstance = new TrayC();
			}
			return sInstance;
		}

		void TrayC::Release() {
			delete sInstance;
			sInstance = NULL;
		}

		TrayC::TrayC() {
			mTrayed = FALSE;
		}
		TrayC::~TrayC() {}

		void TrayC::Add(HWND hWnd) {
			ShowWindow(hWnd, SW_HIDE); //Hide the window being trayed

			NOTIFYICONDATA nid;
			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.hWnd = hWnd;
			nid.uID = TRAY_ICONUID;
			nid.uVersion = NOTIFYICON_VERSION;
			nid.uCallbackMessage = WM_TRAYMESSAGE;
			HINSTANCE MainwindowHinstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
			nid.hIcon = (HICON)LoadImage(MainwindowHinstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), 0);
			GetWindowText(hWnd, nid.szTip, 128); //get window caption
			nid.szTip[128] = NULL; //just incase
			nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
			Shell_NotifyIcon(NIM_ADD, &nid);
			mTrayed = TRUE;
		}

		void TrayC::Remove(HWND hWnd) {
			NOTIFYICONDATA nid;
			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.hWnd = hWnd;
			nid.uID = TRAY_ICONUID;
			Shell_NotifyIcon(NIM_DELETE, &nid);
			mTrayed = FALSE;
		}

		void TrayC::Restore(HWND hWnd, BOOL IS_MAX) {
			if (IS_MAX) { 
				ShowWindow(hWnd, SW_SHOWMAXIMIZED); 
			} else { 
				ShowWindow(hWnd, SW_SHOWNORMAL); 
			}
			SetForegroundWindow(hWnd);
			Remove(hWnd);
		}

		BOOL TrayC::InTray() {
			return mTrayed;
		}

	}
}