/*! \file	    verbose.cpp
	\brief	    Function definitions for reporting the verbose
	\author	    Manh Khang Vu
	\date	    2024-12-03
	\copyright	Manh Khang Vu

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

  Copyright Manh Khang Vu

  ============================================================= */

#include "../inc/verbose.hpp"
#include "../../0. utilities/utilities.hpp"		
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

namespace fileusage {
	void print_path(const string& path, streamsize count_width) {
		const size_t max_char{ max(horizontal_width - count_width - 1, static_cast<size_t>(85)) - 5 };
		size_t begin{ 0 };

		// Lambda function to find the last break character
		auto find_break_char{ [&](char ch1, char ch2, size_t pos) -> size_t {
			size_t first_break{ path.rfind(ch1, pos) };
			size_t second_break{ path.rfind(ch2, pos) };
			if (first_break == string::npos || second_break == string::npos)
				return min(first_break, second_break);
			else
				return max(first_break, second_break);
		} };

		while (begin < path.size()) {
			size_t end{ min(begin + max_char, path.size()) };
			if (end < path.size()) {
				size_t next_break{ find_break_char('\\', ' ', end - 1) };
				if (next_break != string::npos && next_break > begin + (max(horizontal_width - count_width - 1, static_cast<size_t>(85)) - 25))
					end = next_break + 1;
			}

			if (begin != 0)
				cout << " " << setw(count_width) << "" << bar;

			cout << setw(5) << "" << path.substr(begin, end - begin) << "\n";
			begin = end;
		}
	}

	void print_verbose(const deque<Extension>& ext_deque, size_t largest_count) {
		// Calculate the width of the extension column
		streamsize count_width{ static_cast<streamsize>(max(format_number(largest_count).size(), static_cast<size_t>(3)) + 1) };
		string horizontal_line{ string(count_width, dash) + downward_T + string(max(horizontal_width - count_width - 1, static_cast<size_t>(85)), dash) };

		// Print the header
		print_header("File Directories");

		// Print the extensions' directories
		for (const auto& ext : ext_deque) {
			set_color(GREEN); cout << " " << ext.extension();
			set_color(WHITE); cout << " (";
			set_color(CYAN); cout << format_number(ext.info().count());
			set_color(WHITE); cout << " files - ";
			set_color(CYAN); cout << format_number(ext.info().size());
			set_color(WHITE); cout << " bytes)\n";
			cout << " " << horizontal_line << "\n";

			// Print a sample of the directories only
			const size_t count{ ext.info().paths().size() };
			constexpr size_t num_front{ 8 };
			constexpr size_t num_back{ 3 };
			const size_t low_count{ min(num_front, count) };
			const size_t high_count{ count > low_count ? count - num_back : count };

			// Print the front of the list
			deque<Extension>::size_type i{ 0 };
			for (; i < low_count; ++i) {
				set_color(YELLOW); cout << " " << setw(count_width) << format_number(i + 1);
				set_color(WHITE); cout << bar;
				print_path(ext.info().paths().at(i), count_width);
			}

			// Skip the middle of the list if it is too large
			if (i < high_count) {
				cout << " " << setw(count_width) << "" << bar << "\n";
				set_color(YELLOW); cout << " " << setw(count_width) << "...";
				set_color(WHITE); cout << setw(6) << left << bar << right;
				set_color(YELLOW); cout << "...";
				set_color(WHITE); cout << "\n";
				cout << " " << setw(count_width) << "" << bar << "\n";
				i = high_count;
			}

			// Print the back of the list
			for (; i < count; ++i) {
				set_color(YELLOW); cout << " " << setw(count_width) << format_number(i + 1);
				set_color(WHITE); cout << bar;
				print_path(ext.info().paths().at(i), count_width);
			}
			cout << "\n";
		}
	}
}	// End of namespace fileusage