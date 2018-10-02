#if defined(_MSC_VER)
	#include <Windows.h>
#elif defined(__GNUC__) 
	#define Sleep(x) sleep(x)
#endif
#include "HRTimer.h"

int main()
{
	HRTimer::HRTimer tmr;
	// Start timer
	tmr.Start();
	// Time execution of a nop
	_asm nop;
	// Print result as nano, micro or milli 
	tmr.PrintElapsedTime("Nop");
	// Print result as a double
	tmr.PrintElapsedTimeDbl("Nop");
	// Reset timer
	tmr.Reset();
	// Sleep for 0
	Sleep(0);
	// Print result
	tmr.PrintElapsedTime("Function Call");
	// Reset timer and test using lap functionality
	// for various sleep periods
	tmr.Reset();
	Sleep(0);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(1);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(10);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(100);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(300);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(2020);
	// Save a lap
	tmr.Lap(__LINE__);

	// Print result of all laps as double
	tmr.PrintLapTimesDbl();
	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes(__FUNCTION__);

	return 0;
}

