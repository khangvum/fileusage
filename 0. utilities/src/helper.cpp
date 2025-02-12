/*! \file	    helper.cpp
	\brief	    Helper utilities
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

#include "../inc/constants.hpp"
#include "../inc/helper.hpp"
#include "../inc/system.hpp"
using namespace std;

void print_title() {
	// Save the current color
	save_color();
	atexit(restore_color);

	// Set the codepage to 850
	SetConsoleOutputCP(850);
	atexit(restore_codepage);

	set_color(INVERSE_GREY);
	cout << " fileusage 2.0.0 "s << copyright << "2024-2025, Khang Vu "s;
	set_color(WHITE); cout << "\n\n";
}

void print_header(const string& title) {
	set_color(INVERSE_WHITE); cout << " " << setw(horizontal_width) << left << title << right;
	set_color(WHITE); cout << "\n\n";
}

void find_maxima(const deque<Extension>& ext_deque, streamsize& ext_width, streamsize& count_width, streamsize& size_width, size_t& total_counts, streamsize& total_sizes, size_t& largest_count) {
	for (const auto& ext : ext_deque) {
		if (ext.extension().size() > static_cast<size_t>(ext_width))
			ext_width = ext.extension().size();
		total_counts += static_cast<streamsize>(ext.info().count());
		total_sizes += ext.info().size();

		if (ext.info().count() > largest_count)
			largest_count = ext.info().count();
	}

	ext_width = max(ext_width, static_cast<streamsize>(string("Extension").size())) + 1;
	count_width = static_cast<streamsize>(format_number(total_counts).size() + 5);
	size_width = static_cast<streamsize>(max(format_number(total_sizes).size(), static_cast<size_t>(string("Size").size())) + 5);
}