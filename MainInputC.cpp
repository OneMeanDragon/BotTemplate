#include "MainInputC.h"

namespace Bot
{
	namespace Interface {

		MainInputC* MainInputC::sInstance = NULL;

		MainInputC* MainInputC::Instance() {
			if (sInstance == NULL)
			{
				sInstance = new MainInputC();
			}
			return sInstance;
		}

		void MainInputC::Release() {
			delete sInstance;
			sInstance = NULL;
		}

		MainInputC::MainInputC() { }

		MainInputC::~MainInputC() { }

		void MainInputC::m_hWnd(const HWND hWnd) {
			if (m_hWnd() == NULL) {
				MainHwnd = hWnd;
			}
		}

		HWND MainInputC::m_hWnd() {
			return MainHwnd;
		}

		void MainInputC::InitSubclass() {
			EditBoxOldWndProc = (WNDPROC)SetWindowLong(m_hWnd(), GWL_WNDPROC, (LONG)EditBoxSubclass);
		}

		void MainInputC::KillSubclass() {
			SetWindowLong(m_hWnd(), GWL_WNDPROC, (LONG)EditBoxOldWndProc);
		}

		//MainWindow InputBox subclass.
		LRESULT CALLBACK MainInputC::EditBoxSubclass(HWND EditBox, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			//std::string OutData = "uMsg: " + std::to_string(uMsg) + " \r\n";
			//OutputDebugString(OutData.c_str());
			
			return CallWindowProc(Instance()->EditBoxOldWndProc, EditBox, uMsg, wParam, lParam);
		}

		namespace InputBox
		{

			void SetText(HWND hWnd, char *text) {
				SetWindowText(hWnd, text);
			}

			void GetText(HWND hWnd, char *text) {
				GetWindowText(hWnd, text, MAX_INPUT);
			}

			void AppendText(HWND hWnd, char *text) {
				char buffer[MAX_INPUT] = "";
				GetWindowText(hWnd, buffer, sizeof(buffer));
				sprintf_s(buffer, "%s%s", buffer, text);
				SetWindowText(hWnd, buffer);
			}

		}

	}
}


