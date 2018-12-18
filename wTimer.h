#ifndef _WTIMER_H
#define _WTIMER_H

#include "includes.h"

namespace Bot
{

	namespace Interface
	{

		class wTimer
		{
		private:
			UINT32 mInterval;
			HWND mHwnd;
			_myTimerProc wProcess;

		public:
			wTimer();
			~wTimer();

			void Start(UINT32 i_Interval, const HWND mWindow, const _myTimerProc pFunct);
			void Stop();
			void Reset();

		};

	}

}

#endif
