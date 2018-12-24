#include "MainWindow.h"

namespace Bot {

	MainWindowC* MainWindowC::sInstance = NULL;

	MainWindowC* MainWindowC::Instance() {
		if (sInstance == NULL)
		{
			sInstance = new MainWindowC();
		}
		return sInstance;
	}

	void MainWindowC::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	MainWindowC::MainWindowC() {
		MainInstance = NULL;
		MainHwnd = NULL;
		MainIcon = NULL;

		//load the richedit dll
		HINSTANCE RichEditDLL = LoadLibrary("Riched20.dll");

		mMaximized = FALSE;

		MyMenu = Bot::Interface::mMenu::Instance();
		Tray = Bot::Interface::TrayC::Instance();
		InputBox = Bot::Interface::MainInputC::Instance();

		MyWindows = new wResize();
		MyTimer1 = new Bot::Interface::wTimer();
		MyTimer2 = new Bot::Interface::wTimer();
	}
	MainWindowC::~MainWindowC() {
		Bot::Interface::mMenu::Release();
		MyMenu = NULL;

		Bot::Interface::TrayC::Release();
		Tray = NULL;

		Bot::Interface::MainInputC::Release();
		InputBox = NULL;

		//Unload the richedit dll
		FreeLibrary(RichEditDLL);
		RichEditDLL = NULL;

		delete MyWindows;
		MyWindows = NULL;

		delete MyTimer1;
		MyTimer1 = NULL;
		delete MyTimer2;
		MyTimer2 = NULL;

	}

	//Applications Hinstance
	void MainWindowC::hInst(const HINSTANCE hInstance) { //Set hInstance
		if (hInst() == NULL) {
			MainInstance = hInstance;
		}
	}
	HINSTANCE MainWindowC::hInst() { //Get hInstance
		return MainInstance;
	}
	//MainHwnd
	void MainWindowC::m_hWnd(const HWND hWnd) {
		if (m_hWnd() == NULL) {
			MainHwnd = hWnd;
		}
	}
	HWND MainWindowC::m_hWnd() {
		return MainHwnd;
	}

	//Init and run the window
	void MainWindowC::Run() {
		//run the dialog window.
		DialogBox(hInst(), MAKEINTRESOURCE(IDD_MAINFORM), NULL, DialogProc);
	}

	INT_PTR CALLBACK MainWindowC::DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Instance()->m_hWnd(hWnd);

		switch (message)
		{

		case WM_TIMER: { return Instance()->OnTimer(wParam, lParam); }
		case WM_SETFONT: { return TRUE;	}
		case WM_COMMAND: { if (lParam != 0) { return TRUE; } return Instance()->OnCommand(hWnd, wParam, lParam); }
		case WM_INITDIALOG: { return Instance()->OnInitalization(hWnd);	}
		case WM_PAINT: { return Instance()->OnPaint(hWnd); }
		case WM_CLOSE: { return Instance()->OnClose(hWnd); }
		case WM_DESTROY: { Instance()->InputBox->KillSubclass(); PostQuitMessage(0); break; }
		case WM_SIZE: { return Instance()->OnSize(hWnd, wParam); }
		case WM_NOTIFY: { return Instance()->OnNotify(hWnd, wParam, lParam); }
		case WM_MOVE: {	return TRUE; }
		case WM_TRAYMESSAGE: { return Instance()->OnTray(hWnd, lParam); }
		case WM_CTLCOLOREDIT: { return Instance()->OnCTRLColor(wParam); }
		case WM_CTLCOLORSTATIC: { return Instance()->OnCTRLColor(wParam); }

		}
		//144, 2, 130
		return FALSE;
	}
	int MainWindowC::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		//wCommand dosent mean a damn to me at this point now.
		WORD wCommand = LOWORD(wParam);
		//HWND wValidate = GetDlgItem(m_hWnd(), wCommand);
		//if (wValidate == (HWND)lParam && lParam != 0)
		//{
			//WORD wCommand2 = HIWORD(wParam);
			//EN_SETFOCUS;  0x0100 - 256
			//EN_KILLFOCUS; 0x0200 - 512
			//EN_CHANGE; 0x0300 - 768
			//EN_UPDATE; 0x0400 - 1024
			//window command message.
		//	std::string outdata = "OnCommand: \r\n hWnd (" + std::to_string((DWORD)wValidate) + ") \r\n LPARAM (" + std::to_string((UINT64)lParam) + ") \r\n HICMD(" + std::to_string((UINT64)HIWORD(wParam)) + ")\r\n\r\n";
		//	OutputDebugString(outdata.c_str());
		//	return TRUE;
		//}
		//if (lParam != 0) { return TRUE; } //Window messages flying through the WM_COMMAND procedure..
		//The above is blocked at the dialog proc level now.

		WORD wP1, wP2 = 0;
		wP1 = LOWORD(wParam);
		wP2 = HIWORD(wParam);

		std::string outdata = "OnCommand: \r\n hWnd (" + std::to_string((DWORD)hWnd) + ") \r\n WPARAM (" + std::to_string((UINT64)wParam) + ") \r\n LPARAM (" + std::to_string((UINT64)lParam) + ") \r\n" + std::to_string((UINT64)wP1) + "  \r\n" + std::to_string((UINT64)wP2) + ") \r\n\r\n";
		OutputDebugString(outdata.c_str());

		//return TRUE; //OTHERWISE WE NEED A RETURN RESULT
		//WM_COMMAND holds the function pointer similar to WM_TIMER
		return reinterpret_cast <_myMenuProc> (wParam)(lParam);
	}
	int MainWindowC::OnInitalization(HWND hWnd)
	{
		//set icon
		MainIcon = LoadIcon(hInst(), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)MainIcon);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)MainIcon);

		//set font
		HFONT hFont = CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Consolas"));
		SendMessage(hWnd, WM_SETFONT, WPARAM(hFont), TRUE);

		//set windows in the anchor class
		InputBox->m_hWnd(GetDlgItem(m_hWnd(), IDC_MAININPUTBOX));
		MyWindows->AddWindow(m_hWnd(), InputBox->m_hWnd(), false, true, true, true);
		InputBox->InitSubclass(); //Setup the subclass.
		Bot::Interface::InputBox::SetText(InputBox->m_hWnd(), (char *)("Window Template"));

		//set menu.
		MyMenu->m_hWnd(m_hWnd());


		//set temp timer
		MyTimer1->Start(500, m_hWnd(), (Instance()->TmpTimerProc));
		MyTimer2->Start(1500, m_hWnd(), (Instance()->TmpTimerProc2));
		return TRUE;
	}
	int MainWindowC::OnPaint(HWND hWnd) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(Common::DefColors::BLACK));
		EndPaint(hWnd, &ps);
		return TRUE;
	}
	int MainWindowC::OnCTRLColor(WPARAM wParam) {
		SetBkColor((HDC)wParam, Common::DefColors::BLACK);
		SetTextColor((HDC)wParam, Common::DefColors::WHITE);
		return (BOOL)GetStockObject(BLACK_BRUSH);
	}
	int MainWindowC::OnTray(HWND hWnd, LPARAM lParam) {
		if (lParam == WM_LBUTTONDOWN || lParam == WM_RBUTTONDOWN) {
			Instance()->Tray->Restore(hWnd, Instance()->mMaximized);
		}
		return TRUE;
	}
	int MainWindowC::OnClose(HWND hWnd) {
		if (MessageBox(hWnd, TEXT("Are you sure you want to exit?"), TEXT("Question:"), MB_YESNO) == IDYES)
		{
			if (Tray->InTray()) { Tray->Remove(hWnd); }
			return DestroyWindow(hWnd);
		}
		return FALSE;
	}
	int MainWindowC::OnSize(HWND hWnd, WPARAM wParam) {

		switch (wParam)
		{
			case SIZE_MINIMIZED: {
				Tray->Add(hWnd);
				break;
			}
			case SIZE_RESTORED: {
				mMaximized = FALSE;
				break;
			} //window calls restored when sizeing
			case SIZE_MAXIMIZED: { // No longer needed as the size routien now works perfect
				mMaximized = TRUE;
				break;
			}
			//case SIZE_MAXSHOW: { return TRUE; }
			//case SIZE_MAXHIDE: { return TRUE; }
		}

		return MyWindows->ResizeWindows();
	}
	int MainWindowC::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
		return TRUE;
	}
	int MainWindowC::OnTimer(WPARAM wParam, LPARAM lParam) {
		return reinterpret_cast <_myTimerProc> (wParam)(lParam);
	}
	BOOL WINAPI MainWindowC::TmpTimerProc(LPARAM lParam)
	{
		//OutputDebugString("TmpTimerProc: Tick.\r\n");
		return TRUE;
	}
	BOOL WINAPI MainWindowC::TmpTimerProc2(LPARAM lParam)
	{
		//OutputDebugString("TmpTimerProc2: Tick.\r\n");
		return TRUE;
	}
}
