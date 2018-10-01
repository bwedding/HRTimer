#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

namespace HRTimer
{
	using TimePoint		= std::chrono::high_resolution_clock::time_point;
	using DurationDbl	= std::chrono::duration<double>;
	using DurationSecs	= long long;
	using HiResClk		= std::chrono::high_resolution_clock;
	using DurationMs	= std::chrono::duration<float, std::milli>;
	using DurationUs	= std::chrono::duration<float, std::micro>;
	using DurationNs	= std::chrono::duration<float, std::nano>;
	using Laps			= std::vector<TimePoint>;

	class HRTimer
	{
	public:
		void Start();
		void Reset();
		void Stop();
		void Lap();
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
