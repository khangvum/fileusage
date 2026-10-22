/*! \file	    summary.cpp
	\brief	    Function definitions for reporting the summary
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

#include "../inc/summary.hpp"
#include "../inc/verbose.hpp"		
#include "../../0. utilities/utilities.hpp"
#include <print>
#include <algorithm>
using namespace std;

namespace fileusage {
	void print_summary(const deque<Extension>& ext_deque, const Argument& arguments) {
		// Calculate the widths of the columns, the total counts & sizes
		// and fin the largest count
		streamsize ext_width{ 0 }, count_width{ 0 }, size_width{ 0 };
		size_t total_counts{ 0 };
		streamsize total_sizes{ 0 };

		size_t largest_count{ 0 };

		find_maxima(ext_deque, ext_width, count_width, size_width, total_counts, total_sizes, largest_count);
		string horizontal_line{ string(ext_width, dash) + cross + string(count_width, dash) + cross + string(size_width, dash) };
		horizontal_width = horizontal_line.size();

		// If there is a verbose request, print the file directories
		if (arguments.verbose() && !ext_deque.empty()) {
			print_verbose(ext_deque, largest_count);
		}

		// Print the header
		print_header("Summary");
		print(" {:>{}}{}{:>{}}{}{:>{}}\n", "Extension", ext_width, bar, "#", count_width, bar, "Size", size_width);
		print(" {}\n", horizontal_line);

		// Print the extensions' information
		for (const auto& ext : ext_deque) {
			set_color(CYAN); print(" {:>{}}", ext.extension(), ext_width);
			set_color(WHITE); print("{}", bar);
			set_color(CYAN); print("{:>{}}", format_number(ext.info().count()), count_width);
			set_color(WHITE); print("{}", bar);
			set_color(CYAN); print("{:>{}}", format_number(ext.info().size()), size_width);
            set_color(WHITE); print("\n");
        }

		// Print the total
		print(" {}\n", horizontal_line);
		set_color(GREEN); print(" {:>{}}", format_number(ext_deque.size()), ext_width);
		set_color(WHITE); print("{}", bar);
		set_color(GREEN); print("{:>{}}", format_number(total_counts), count_width);
		set_color(WHITE); print("{}", bar);
		set_color(GREEN); print("{:>{}}", format_number(total_sizes), size_width);
        set_color(WHITE); print("\n\n");
    }
}	// End of namespace fileusage