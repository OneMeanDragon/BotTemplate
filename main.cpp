#include "MainWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//Global Data
	GlobalData::gAppData* mGlobals = GlobalData::gAppData::Instance();
	//Bot
	Bot::MainWindowC* BotWindow = Bot::MainWindowC::Instance();

	BotWindow->hInst(hInstance);
	BotWindow->Run();

	Bot::MainWindowC::Release();
	BotWindow = NULL;
	GlobalData::gAppData::Release();
	mGlobals = NULL;
	return 0;
}