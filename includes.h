#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <Windows.h>
#include <vector>
#include <string>
#include <chrono>


#include "resource.h"

#define TRAY_ICONUID	100				
#define WM_TRAYMESSAGE	(WM_USER + 1)

#define MAX_INPUT 256

typedef BOOL(WINAPI* _myTimerProc)(LPARAM lParam);

//Custom includes
#include "gAppData.h"
#include "wResize.h"
#include "MainInputC.h"
#include "wTimer.h"
#include "Tray.h"

#endif
