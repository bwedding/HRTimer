#include "HRTimer.h"

void emptyFunc(void)
{
	return;
}

void remoteFunc(void)
{
	HRTimer::HiResTimer tmr;
	tmr.Start();
	tmr.HRSleep(std::chrono::milliseconds(200));
	tmr.AutoPrintElapsedTime();
	return;
}

int main()
{
	HRTimer::HiResTimer tmr;
	// Start timer
	tmr.Start();
	// Time execution of a function
	puts("Hello World");
	// Print result as nano, micro or milli 
	tmr.AutoPrintElapsedTime();
	// Print result as a double
	tmr.PrintElapsedTimeDbl();
	// Reset timer
	tmr.Reset();
	// Time function call overhead
	emptyFunc();
	// Print result
	tmr.AutoPrintElapsedTime();

	remoteFunc();
	// Reset timer to test using lap functionality
	// for various sleep periods. 
	// Note: HRSleep is a standard c++ sleep routine 
	// which may be used in place of your own platform 
	// specific sleep() function for portability
	tmr.Reset();
	tmr.HRSleep(std::chrono::milliseconds(1));
	// Save a lap
	tmr.Lap();
	tmr.HRSleep(std::chrono::milliseconds(10));
	// Save a lap
	tmr.Lap();
	tmr.HRSleep(std::chrono::milliseconds(100));
	// Save a lap
	tmr.Lap();
	tmr.HRSleep(std::chrono::milliseconds(333));
	// Save a lap
	tmr.Lap();
	tmr.HRSleep(std::chrono::milliseconds(2020));
	// Save a lap
	tmr.Lap();

	// Print result of all laps as double
	tmr.PrintLapTimesDbl();

	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes();

	// Reset timer and then sleep for a bit and print
	// results of user specified type
	tmr.Reset();
	tmr.HRSleep(std::chrono::milliseconds(1333));

	// Demonstrate printing ET's in specified units
	tmr.PrintElapsedTimeType<std::chrono::nanoseconds>(__func__);
	tmr.PrintElapsedTimeType<std::chrono::microseconds>(__func__);
	tmr.PrintElapsedTimeType<std::chrono::milliseconds>(__func__);
	tmr.PrintElapsedTimeType<std::chrono::seconds>(__func__);

	return 0;
}

