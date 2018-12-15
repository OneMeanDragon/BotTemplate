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
	}
	MainWindowC::~MainWindowC() {}

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
		HINSTANCE RichEditDLL = LoadLibrary("Riched20.dll");

		//run the dialog window.
		DialogBox(hInst(), MAKEINTRESOURCE(IDD_MAINFORM), NULL, DialogProc);

		FreeLibrary(RichEditDLL);
	}

	INT_PTR CALLBACK MainWindowC::DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Instance()->m_hWnd(hWnd);

		switch (message)
		{
		case WM_SETFONT: {
			return TRUE;
		}
		case WM_COMMAND: { return Instance()->OnCommand(hWnd, wParam, lParam); }
		case WM_INITDIALOG: { return Instance()->OnInitalization(hWnd);	}
		case WM_PAINT: { return Instance()->OnPaint(hWnd); }
		case WM_CLOSE: { return Instance()->OnClose(hWnd); }
		case WM_DESTROY: { 
			PostQuitMessage(0); 
			break; }
		case WM_SIZE: { return Instance()->OnSize(hWnd, wParam); }
		case WM_NOTIFY: { return Instance()->OnNotify(hWnd, wParam, lParam); }


		case WM_MOVE: {	return TRUE; }

		case WM_CTLCOLOREDIT:
		case WM_CTLCOLORSTATIC:
			SetBkColor((HDC)wParam, 0x000000);
			SetTextColor((HDC)wParam, 0xFFFFFF);
			return (BOOL)GetStockObject(BLACK_BRUSH);
		}
		//144, 2, 130
		return FALSE;
	}
	int MainWindowC::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
	{
		WORD wCommand = LOWORD(wParam);
		return TRUE; //OTHERWISE WE NEED A RETURN RESULT
	}
	int MainWindowC::OnInitalization(HWND hWnd)
	{
		HFONT hFont = CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Consolas"));
		SendMessage(hWnd, WM_SETFONT, WPARAM(hFont), TRUE);
		return TRUE;
	}
	int MainWindowC::OnPaint(HWND hWnd) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// All painting occurs here, between BeginPaint and EndPaint.
		FillRect(hdc, &ps.rcPaint, (HBRUSH)CreateSolidBrush(RGB(0, 0, 0)));
		EndPaint(hWnd, &ps);
		return TRUE;
	}
	int MainWindowC::OnClose(HWND hWnd) {
		if (MessageBox(hWnd, TEXT("Are you sure you want to exit?"), TEXT("Question:"), MB_YESNO) == IDYES)
		{
			return DestroyWindow(hWnd);
		}
		return FALSE;
	}
	int MainWindowC::OnSize(HWND hWnd, WPARAM wParam) {
		return TRUE;// myWindows.ResizeWindows();
	}
	int MainWindowC::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
		return TRUE;
	}
}