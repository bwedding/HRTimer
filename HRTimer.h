#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>

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
	using milliSecs		= std::chrono::milliseconds;

	class HRTimer
	{
	public:
		void Start();
		void Reset();
		void Stop();
		// Note, the intention is to call this using
		// the __LINE__ macro to print the line number
		// where the lap measurement was taken
		// The default value is set to make it obvious
		// that it's not a line number
		void Lap(int lineNo = INT_MAX );
		void PrintLapTimesDbl(std::string msg = "Function Not Specified");
		void PrintLapTimes(std::string msg = "Function Not Specified");
		void PrintElapsedTimeDbl(std::string msg = "Function Not Specified");
		void AutoPrintElapsedTime(std::string msg = "Function Not Specified");

		// Cross platform sleep provided for convenience
		void HRSleep(milliSecs mSec);

		// If you wish to NOT autoscale your time printouts,
		// You can use this template to print the specified
		// type, from nanoseconds to minutes
		template<typename T2>
		void PrintElapsedTimeType(std::string msg)
		{
			Stop();
			
			std::string type;
			
			switch (switch_value<T2>::value )
			{
			case 1:
				type = " NanoSeconds";
				break;
			case 2:
				type = " MicroSeconds";
				break;
			case 3:
				type = " MilliSeconds";
				break;
			case 4:
				type = " Seconds";
				break;
			case 5:
				type = " Minutes";
				break;
			default:  
				// We can't ever hit this because the template won't
				// compile with an invalid type
				return;
			}

			if (msg.length() > 1)
				msg.append(" ");
			std::cout << msg << "Elapsed time: " << GetTimeinSecsType<T2>() << type << std::endl;
		};

	private:
		DurationSecs	GetTimeInUSecs(void);
		DurationSecs	GetTimeInNSecs(void);
		DurationSecs	GetTimeInSecs(void);
		DurationSecs	GetTimeInMinutes(void);
		DurationSecs	GetTimeInMSecs(void);
		DurationSecs	GetDeltaTime(TimePoint &start, TimePoint &end, std::string &type);
		double			GetElapsedTimeInDbl(void);
		double			GetDeltaTimeInDbl(TimePoint &start, TimePoint &end);

		// Templates
		template<typename T1>
		DurationSecs GetTimeinSecsType()
		{
			return std::chrono::duration_cast<T1>(mEnd - mStart).count();
		}

		template<typename T>
		struct switch_value {};

		template<>
		struct switch_value<std::chrono::nanoseconds>
		{
			enum { value = 1 };
		};

		template<>
		struct switch_value<std::chrono::microseconds>
		{
			enum { value = 2 };
		};

		template<>
		struct switch_value<std::chrono::milliseconds>
		{
			enum { value = 3 };
		};

		template<>
		struct switch_value<std::chrono::seconds>
		{
			enum { value = 4 };
		};

		template<>
		struct switch_value<std::chrono::minutes>
		{
			enum { value = 5 };
		};

		// Member vars
		TimePoint	mStart;
		TimePoint	mEnd;
		Laps		mLaps;
	};
}
