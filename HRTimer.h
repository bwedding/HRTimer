#pragma once

// Hi Resolution timer. Cross-platform Standard C++ 11. Tested on MSVC 2015, Clange 9.0 and GCC 8.0
// Copyright Bruce D Wedding 2018

#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>

// Cross platform sleep
#define HRSleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

namespace HRTimer
{
	using TimePoint		= std::chrono::high_resolution_clock::time_point;
	using LapMarker		= struct { TimePoint tp; std::string line; };
	using DurationDbl	= std::chrono::duration<double>;
	using DurationSecs	= long long;
	using HiResClk		= std::chrono::high_resolution_clock;
	using DurationMs	= std::chrono::duration<float, std::milli>;
	using DurationUs	= std::chrono::duration<float, std::micro>;
	using DurationNs	= std::chrono::duration<float, std::nano>;
	using Laps			= std::vector<LapMarker>;

	class HRTimer
	{
	public:
		void Start();
		void Reset();
		void Stop();
		void Lap(int lineNo = 0);
		void PrintLapTimesDbl(std::string msg = "");
		void PrintLapTimes(std::string msg = "");
		void PrintElapsedTimeDbl(std::string msg = "");
		void PrintElapsedTime(std::string msg = "");

	private:
		DurationSecs	GetTimeInUSecs(void);
		DurationSecs	GetTimeInNSecs(void);
		DurationSecs	GetTimeInSecs(void);
		DurationSecs	GetTimeInMinutes(void);
		DurationSecs	GetTimeInMSecs(void);
		DurationSecs	GetDeltaTime(TimePoint &start, TimePoint &end, std::string &type);
		double			GetElapsedTimeInDbl(void);
		double			GetDeltaTimeInDbl(TimePoint &start, TimePoint &end);

		// Member vars
		TimePoint	mStart;
		TimePoint	mEnd;
		Laps		mLaps;
	};
}
