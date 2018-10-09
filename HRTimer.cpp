#include "HRTimer.h"

namespace HRTimer
{
	// Clears all current laps and takes
	// a fresh timestamp. 
	void HiResTimer::Start()
	{
		mLaps.clear();
		mStart = mEnd = HiResClk::now();
	};

	// Resets timer to start a fresh set
	// of measurements
	void HiResTimer::Reset()
	{
		Start();
	};

	// Stops the timer, which is to say, it
	// takes and ending timestamp
	void HiResTimer::Stop()
	{
		mEnd = std::chrono::high_resolution_clock::now();
	};

	// Saves a LapMarker, which is a line number and timestamp at this moment
	// To function as intended, this should be called using the __LINE__ macro
	// so that it will print the line number where the timepoint is measured
	void HiResTimer::Lap(int line)
	{
		LapMarker currentMark;
		currentMark.tp = HiResClk::now();
		currentMark.line = std::to_string(line);
		mLaps.push_back(currentMark);
	};

	// Prints all the saved Lap times as a double, with line numbers
	void HiResTimer::PrintLapTimesDbl(std::string msg)
	{
		TimePoint start = mStart;
		for (auto lap : mLaps)
		{
			std::cout << std::setprecision(3) << msg << "Line: " << lap.line << " Lap time: " << GetDeltaTimeInDbl(start, lap.tp) << " seconds" << std::endl;
			start = lap.tp;
		}
	}

	// Prints all the saved Lap times, scaled to the appropriate seconds type, with line numbers
	// To function as intended, this should be called using the __FUNC__ macro
	// so that it will print the line number where the timepoint is measured
	void HiResTimer::PrintLapTimes(std::string funcName)
	{
		TimePoint start = mStart;
		std::string type;
		for (auto lap : mLaps)
		{
			std::cout << std::setprecision(3) << funcName << "Line: " << lap.line << " - Lap time: " << GetDeltaTime(start, lap.tp, type) << type << std::endl;
			start = lap.tp;
		}
	}

	// Prints all the saved Lap times as a double, with line numbers
	// To function as intended, this should be called using the __FUNC__ macro
	// so that it will print the line number where the timepoint is measured
	void HiResTimer::PrintElapsedTimeDbl(std::string funcName)
	{
		Stop();
		if (funcName.length() > 1)
			funcName.append(" ");
		std::cout << std::setprecision(3) << funcName << "Elapsed time: " << GetElapsedTimeInDbl() << " seconds" << std::endl;
	}

	// Prints ET in most reasonable format from nanoseconds to minutes
	// Optionally prints a passed in message
	void HiResTimer::AutoPrintElapsedTime(std::string msg)
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

	DurationSecs HiResTimer::GetTimeInUSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(mEnd - mStart).count();
	}

	DurationSecs HiResTimer::GetTimeInNSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(mEnd - mStart).count();
	}

	DurationSecs HiResTimer::GetTimeInSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::seconds>(mEnd - mStart).count();
	}

	DurationSecs HiResTimer::GetTimeInMinutes(void)
	{
		return std::chrono::duration_cast<std::chrono::minutes>(mEnd - mStart).count();
	}

	DurationSecs HiResTimer::GetTimeInMSecs(void)
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(mEnd - mStart).count();
	}

	double HiResTimer::GetElapsedTimeInDbl(void)
	{
		return std::chrono::duration_cast<DurationDbl>(mEnd - mStart).count();
	}

	double HiResTimer::GetDeltaTimeInDbl(TimePoint &start, TimePoint &end)
	{
		return std::chrono::duration_cast<DurationDbl>(end - start).count();
	}

	// A standard C++, platform independent sleep method
	// provided for portability and convenience
	void HiResTimer::HRSleep(milliSecs mSec)
	{ 
		std::this_thread::sleep_for(milliSecs(mSec));
	};

	// Returns a duration delta between 2 timepoints of the most appropriate type
	// Note, it does not break types on exact boundaries but a bit beyond (2000 units). 
	// This is because the loss of precision may not be desired.
	// e.g. If the delta is 1743 nanoseconds, the end user would probably prefer 
	// seeing that precise value instead of 2 microseconds
	DurationSecs HiResTimer::GetDeltaTime(TimePoint &start, TimePoint &end, std::string &type)
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
