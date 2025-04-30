#pragma once
/*! \file	    benchmark.hpp
	\brief	    Function declarations for reporting the benchmark
	\author	    Khang Vu
	\date	    2024-12-03
	\copyright	Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2024.12.03
	  Directory hierarchy cleanup
	  Separated system, constants, and helper utilities

  Version 2024.11.05
	  Classes cleanup

  Version 2024.06.18
	  Added ThreadPool

  Version 2024.04.19
	  Alpha release

  =============================================================

  Copyright Khang Vu

  ============================================================= */

#include <string>
#include <chrono>
using hour_clock = std::chrono::high_resolution_clock;

namespace fileusage {
	extern long long elapsed_time;

	/*	\brief		Print the time
		\param		const std::string& title	- The title
					hour_clock::duration		- The time duration
	*/
	void print_time(const std::string& title, hour_clock::duration time);

	/*	\brief		Print the interval time
		\param		hour_clock::time_point	- The start time
					hour_clock::time_point	- The time after scanning
					hour_clock::time_point	- The time after sorting
					hour_clock::time_point	- The stop time
	 */
	void print_interval_times(hour_clock::time_point start, hour_clock::time_point after_scan, hour_clock::time_point after_sort, hour_clock::time_point stop);
}	// End of namespace fileusage