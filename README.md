# HRTimer
Standard C++ High Resolution Timer with lap functionality. Accurate to within nanoseconds. The print routines automatically scale the result to nanoseconds, microseconds, milliseconds, seconds or minutes, depending on the size of the value.

The Lap method will save line numbers and print them out when the print method is called. e.g.

	HRTimer::HRTimer tmr;
	// Start timer
	tmr.Start();
	// Time execution of a nop
	_asm nop;
	// Print result as nano, micro or milli 
	tmr.PrintElapsedTime("Nop");
	// Reset timer
	tmr.Reset();
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(1);
	// Save a lap
	tmr.Lap(__LINE__);
	Sleep(10);
	// Print result of all laps as nano, micro, milli, etc
	tmr.PrintLapTimes(__FUNCTION__);
  
  Outputs:
Nop Elapsed time: 400 NanoSeconds
main Line: 21 - Lap time: 300 NanoSeconds
main Line: 24 - Lap time: 1247 MicroSeconds
