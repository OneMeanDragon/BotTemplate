#include "MainWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	Bot::MainWindowC* BotWindow = Bot::MainWindowC::Instance();

	BotWindow->hInst(hInstance);
	BotWindow->Run();

	Bot::MainWindowC::Release();
	BotWindow = NULL;
	return 0;
}