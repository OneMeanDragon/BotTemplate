#include "gAppData.h"

namespace GlobalData
{

	gAppData* gAppData::sInstance = NULL;

	gAppData* gAppData::Instance() {
		if (sInstance == NULL)
		{
			sInstance = new gAppData();
		}
		return sInstance;
	}

	void gAppData::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	gAppData::gAppData() {
		//Application start time
		time(&mApplicationStartTime);
		mComputerStartTime = InitCpuStart();
	}
	gAppData::~gAppData() {}

	time_t gAppData::InitCpuStart()
	{
		//Computer start time.
		LARGE_INTEGER freq;
		LARGE_INTEGER ll_start_time;
		//time_t computer_started_time;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&ll_start_time);
		time_t time_value_now;
		time(&time_value_now);
		time_t cpu_start = time_value_now - ((time_t)ll_start_time.QuadPart / freq.QuadPart);

		return cpu_start;
	}

	time_t gAppData::ApplicationStartTime()
	{
		return mApplicationStartTime;
	}

	time_t gAppData::ComputerStartTime()
	{
		return mComputerStartTime;
	}

}