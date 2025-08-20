/*! \file	    Argument.cpp
	\brief	    Argument class definition
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

#include "../inc/Argument.hpp"
#include <iostream>
#include <deque>
#include <regex>
#include <cstdlib>
using namespace std;

namespace fileusage {
	// Method
	void Argument::parse(int argc, char* argv[]) {
		// Load the arguments, excluding the executable file name
		deque<string> args_deque(argv + 1, argv + argc);

		// Parse the arguments
		deque<string>::iterator args_it;
		for (args_it = begin(args_deque); args_it != end(args_deque); ++args_it) {
			if (*args_it == "--help") {
				help_ = true;
			}
			else if (regex_match(*args_it, std::regex("^-[a-z]+$"))) {
				for (const char& c : string(begin(*args_it) + 1, end(*args_it))) {
					switch (c) {
					case 'h': help_ = true; break;
					case 'd': reverse_ = true; break;
					case 'r': suppress_recursive_ = true; break;
					case 's': sort_by_size_ = true; break;
					case 'v': verbose_ = true; break;
					case 'b': benchmark_ = true; break;
					case 'x':
						regex_ = true;
						if (++args_it != end(args_deque)) {
							regex_pattern_ = *args_it;
							break;
						}
						else {
							cerr << "Error: Error: -x switch used without regular expression argument provided.\n";
							exit(EXIT_FAILURE);
						}
					}
				}
			}
			else {
				dir_path_ = *(args_it++);
				break;
			}
		}

		if (args_it != end(args_deque) && !help_) {
			cerr << "Error: Error: Too many commandline arguments: "s << *args_it << "...\n";
			exit(EXIT_FAILURE);
		}
		else if (!filesystem::is_directory(dir_path_)) {
			cerr << "Error: Canonical: The system cannot find the file specified: \""s << dir_path_ << "\"\n";
			exit(EXIT_FAILURE);
		}
	}
}	// End of namespace fileusage