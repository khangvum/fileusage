/*! \file	    benchmark.cpp
	\brief	    Function definitions for reporting the benchmark
	\author	    Manh Khang Vu
	\date	    2024-12-03
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2026.10.22
	  Added singleton pattern to application

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

  Copyright Manh Khang Vu

  ============================================================= */

#include "../inc/benchmark.hpp"
#include "../../0. utilities/utilities.hpp"
#include <print>
using namespace std;

namespace fileusage {
	long long elapsed_time{};

	void print_time(const string& title, hour_clock::duration time) {
		auto nano_seconds{ chrono::duration_cast<chrono::nanoseconds>(time).count() };
		print(" {:>{}}: ", title, 12);
		set_color(YELLOW); print("{:>{}}", format_number(nano_seconds), format_number(elapsed_time).size());
		set_color(WHITE); print(" ns -> ");
		set_color(YELLOW); print("{:>{}}", format_number(nano_seconds / 1.0E9, 2), format_number(elapsed_time / 1.0E9, 2).size());
		set_color(WHITE); print(" s.\n");
	}

	void print_interval_times(hour_clock::time_point start, hour_clock::time_point after_scan, hour_clock::time_point after_sort, hour_clock::time_point stop) {
		print_header("Benchmark");

		elapsed_time = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
		print_time("Elapsed time", stop - start);
		print_time("Scan time", after_scan - start);
		print_time("Sort time", after_sort - after_scan);
		print_time("Report time", stop - after_sort);
	}
}	// End of namespace fileusage