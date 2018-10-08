#include "HRTimer.h"

int main()
{
	HRTimer::HRTimer tmr;
	// Start timer
	tmr.Start();
	// Time execution of a function
	puts("Hello World");
	// Print result as nano, micro or milli 
	tmr.AutoPrintElapsedTime("puts()");
	// Print result as a double
	tmr.PrintElapsedTimeDbl("puts()");
	// Reset timer
	tmr.Reset();
	// Sleep for 0
	tmr.HRSleep(std::chrono::milliseconds(0));
	// Print result
	tmr.AutoPrintElapsedTime("Function Call");
	// Reset timer and test using lap functionality
	// for various sleep periods
	tmr.Reset();
	tmr.HRSleep(std::chrono::milliseconds(1));
	// Save a lap
	tmr.Lap(__LINE__);
	tmr.HRSleep(std::chrono::milliseconds(10));
	// Save a lap
	tmr.Lap(__LINE__);
	tmr.HRSleep(std::chrono::milliseconds(100));
	// Save a lap
	tmr.Lap(__LINE__);
	tmr.HRSleep(std::chrono::milliseconds(333));
	// Save a lap
	tmr.Lap(__LINE__);
	tmr.HRSleep(std::chrono::milliseconds(2020));
	// Save a lap
	tmr.Lap(__LINE__);

	// Print result of all laps as double
	tmr.PrintLapTimesDbl();
	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes(__FUNCTION__);

	tmr.Reset();
	tmr.HRSleep(std::chrono::milliseconds(1333));

	tmr.PrintElapsedTimeType<std::chrono::nanoseconds>(__FUNCTION__);
	tmr.PrintElapsedTimeType<std::chrono::microseconds>(__FUNCTION__);
	tmr.PrintElapsedTimeType<std::chrono::milliseconds>(__FUNCTION__);
	tmr.PrintElapsedTimeType<std::chrono::seconds>(__FUNCTION__);

	return 0;
}

