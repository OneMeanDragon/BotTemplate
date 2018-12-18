#include "wTimer.h"

namespace Bot
{

	namespace Interface
	{

		wTimer::wTimer()
		{
			mInterval = 0;
			wProcess = NULL;
			mHwnd = NULL;
		}

		wTimer::~wTimer()
		{
			mInterval = 0;
			wProcess = NULL;
			mHwnd = NULL;
		}

		void wTimer::Start(UINT32 i_Interval, const HWND mWindow, _myTimerProc pFunct)
		{
			mInterval = i_Interval;
			wProcess = pFunct; //reinterpret_cast <_myTimerProc>(pFunct); //pFunct;
			mHwnd = mWindow;

			SetTimer(mHwnd, (UINT_PTR)wProcess, mInterval, (TIMERPROC)NULL);
		}

		void wTimer::Stop()
		{
			KillTimer(mHwnd, (UINT_PTR)wProcess);
		}

		void wTimer::Reset()
		{
			KillTimer(mHwnd, (UINT_PTR)wProcess);
			SetTimer(mHwnd, (UINT_PTR)wProcess, mInterval, (TIMERPROC)NULL);
		}

	}

}