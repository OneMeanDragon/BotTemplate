#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <Windows.h>
#include <vector>
#include <string>


#include "resource.h"

#define TRAY_ICONUID	100				
#define WM_TRAYMESSAGE	(WM_USER + 1)

typedef BOOL(WINAPI* _myTimerProc)(LPARAM lParam);

//Custom includes
#include "wResize.h"
#include "MainInputC.h"
#include "wTimer.h"

#endif

