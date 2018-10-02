#include "HRTimer.h"

namespace HRTimer
{
	void HRTimer::Start()
	{
		mLaps.clear();
		mStart = mEnd = HiResClk::now();
	};

	void HRTimer::Reset()
	{
		Start();
	};

	void HRTimer::Stop()
	{
		mEnd = std::chrono::high_resolution_clock::now();
	};

	void HRTimer::Lap(int line)
	{
		LapMarker currentMark;
		currentMark.tp = HiResClk::now();
		currentMark.line = std::to_string(line);
		mLaps.push_back(currentMark);
	};

	void HRTimer::PrintLapTimesDbl(std::string msg)
	{
		TimePoint start = mStart;
		for (auto lap : mLaps)
		{
			std::cout << std::setprecision(3) << msg << " Line:" << lap.line << " Lap time: " << GetDeltaTimeInDbl(start, lap.tp) << " seconds" << std::endl;
			start = lap.tp;
		}
	}

	void HRTimer::PrintLapTimes(std::string funcName)
	{
		TimePoint start = mStart;
		std::string type;
		for (auto lap : mLaps)
		{
			std::cout << std::setprecision(3) << funcName << " Line: " << lap.line << " - Lap time: " << GetDeltaTime(start, lap.tp, type) << type << std::endl;
			start = lap.tp;
		}
	}

	void HRTimer::PrintElapsedTimeDbl(std::string funcName)
	{
		Stop();
		if (funcName.length() > 1)
			funcName.append(" ");
		std::cout << std::setprecision(3) << funcName << "Elapsed time: " << GetElapsedTimeInDbl() << " seconds" << std::endl;
	}

	// Prints ET in most reasonable format from nano Seconds to minutes
	// Optionally prints a passed in message
	void HRTimer::PrintElapsedTime(std::string msg)
	{
		Stop();
		std::string type = " NanoSeconds";
		DurationSecs tmp = GetTimeInNSecs();
		if (tmp > 2000)
		{
			tmp = GetTimeInUSecs();
			type = " MicroSeconds";
			if (tmp > 2000)
			{
				tmp = GetTimeInMSecs();
				type = " MilliSeconds";
				if (tmp > 2000)
				{
					tmp = GetTimeInSecs();
					type = type = " Seconds";
					if (tmp > 120)  // 2 minutes
					{
						tmp = GetTimeInMinutes();
						type = type = " Minutes";
					}
				}
			}
		}
		if (msg.length() > 1)
			msg.append(" ");
		std::cout << msg << "Elapsed time: " << tmp << type << std::endl;
	}

	DurationSecs HRTimer::GetTimeInUSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(mEnd - mStart).count();
	}

	DurationSecs HRTimer::GetTimeInNSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(mEnd - mStart).count();
	}

	DurationSecs HRTimer::GetTimeInSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::seconds>(mEnd - mStart).count();
	}

	DurationSecs HRTimer::GetTimeInMinutes(void)
	{
		return std::chrono::duration_cast<std::chrono::minutes>(mEnd - mStart).count();
	}

	DurationSecs HRTimer::GetTimeInMSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(mEnd - mStart).count();
	}

	double HRTimer::GetElapsedTimeInDbl(void)
	{
		return std::chrono::duration_cast<DurationDbl>(mEnd - mStart).count();
	}

	double HRTimer::GetDeltaTimeInDbl(TimePoint &start, TimePoint &end)
	{
		return std::chrono::duration_cast<DurationDbl>(end - start).count();
	}

	DurationSecs HRTimer::GetDeltaTime(TimePoint &start, TimePoint &end, std::string &type)
	{
		DurationSecs tp;
		Stop();
		type = " NanoSeconds";
		tp = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		if (tp > 2000)
		{
			tp = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();;
			type = " MicroSeconds";
			if (tp > 2000)
			{
				tp = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();;
				type = " MilliSeconds";
				if (tp > 2000)
				{
					tp = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();;
					type = " Seconds";
					if (tp > 120)  // 2 minutes
					{
						tp = std::chrono::duration_cast<std::chrono::minutes>(end - start).count();;
						type = " Minutes";
					}
				}
			}
		}

		return tp;
	}
}
