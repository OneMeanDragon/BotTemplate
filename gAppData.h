#ifndef _GAPPDATA_H
#define _GAPPDATA_H

#include "includes.h"

namespace GlobalData
{

	class gAppData
	{
	private:
		static gAppData* sInstance;

		time_t mApplicationStartTime;
		time_t mComputerStartTime;

	public:
		static gAppData* Instance();
		static void Release();

		time_t ApplicationStartTime();
		time_t ComputerStartTime();

	private:
		gAppData();
		~gAppData();

		time_t InitCpuStart();

	};

}

#endif
