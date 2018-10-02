#include "HRTimer.h"

int main()
{
	HRTimer::HRTimer tmr;
	// Start timer
	tmr.Start();
	// Time execution of a function
	puts("Hello World");
	// Print result as nano, micro or milli 
	tmr.PrintElapsedTime("puts()");
	// Print result as a double
	tmr.PrintElapsedTimeDbl("puts()");
	// Reset timer
	tmr.Reset();
	// Sleep for 0
	HRSleep(0);
	// Print result
	tmr.PrintElapsedTime("Function Call");
	// Reset timer and test using lap functionality
	// for various sleep periods
	tmr.Reset();
	HRSleep(1);
	// Save a lap
	tmr.Lap(__LINE__);
	HRSleep(10);
	// Save a lap
	tmr.Lap(__LINE__);
	HRSleep(100);
	// Save a lap
	tmr.Lap(__LINE__);
	HRSleep(333);
	// Save a lap
	tmr.Lap(__LINE__);
	HRSleep(2020);
	// Save a lap
	tmr.Lap(__LINE__);

	// Print result of all laps as double
	tmr.PrintLapTimesDbl();
	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes(__FUNCTION__);

	return 0;
}

