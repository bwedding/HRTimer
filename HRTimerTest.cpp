// ConsoleApplication20.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
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
	tmr.Lap();
	Sleep(1);
	// Save a lap
	tmr.Lap();  
	Sleep(10);
	// Save a lap
	tmr.Lap();
	Sleep(100);
	// Save a lap
	tmr.Lap();
	Sleep(300);
	// Save a lap
	tmr.Lap();
	Sleep(2020);
	// Save a lap
	tmr.Lap();
	// Print result of all laps as double
	tmr.PrintLapTimesDbl();
	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes(__FUNCTION__);

	return 0;
}

