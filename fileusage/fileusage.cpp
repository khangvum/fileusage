/*! \file	    fileusage.cpp
	\brief	    File usage listing
	\author	    Manh Khang Vu
	\date	    2024-12-03
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2026.10.23
	  Updated to C++23
	  Improved ThreadPool synchronization

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

#include "ConsoleApp.hpp"
#include "fileusage.hpp"
#include <cstdlib>
#include <print>
#include <regex>
using namespace std;

namespace fileusage {
	/*! \class	    FileusageApp
		\brief	    Fileusage application class
	*/
	MAKEAPP(FileusageApp) {
		// Parse the command line arguments
		parse_arguments();

		// Print the title
		print_title();

		// If there is a help request, print the help message and exit
		if (arguments_.help()) {
			print_help();
			return EXIT_SUCCESS;
		}

		// Else, begin the program by printing the folder path
		set_color(INVERSE_RED); print(" Folder: ");
		set_color(RED); print(" {}", arguments_.dir_path());
		set_color(WHITE); print("\n\n");

		// === 1. Start time ===========================================
		auto start{ hour_clock::now() };

		// Scan through the directory and store the extensions' information in a deque
		deque<Extension> ext_deque;
		scan_directory(ext_deque, arguments_);

		// === 2. Scan time ============================================
		auto after_scan{ hour_clock::now() };

		// Sort the deque based on -s and -r switches
		sort_deque(ext_deque, arguments_);

		// === 3. Sort time ============================================
		auto after_sort{ hour_clock::now() };

		// Print the result to the console
		print_summary(ext_deque, arguments_);

		// === 2. Stop time ============================================
		auto stop{ hour_clock::now() };

		// If there is a benchmark request, print the benchmark
		if (arguments_.benchmark()) {
			print_interval_times(start, after_scan, after_sort, stop);
		}

		return EXIT_SUCCESS;
	}

	void FileusageApp::parse_arguments() {
		const CommandLineArgs args_deque{ args() };

		// Parse the arguments
		CommandLineArgs::const_iterator args_it;
		for (args_it = begin(args_deque) + 1; args_it != end(args_deque); ++args_it) {
			if (*args_it == "--help") {
                arguments_.help(true);
			}
			else if (regex_match(*args_it, regex("^-[a-z]+$"))) {
				for (const char& c : string(begin(*args_it) + 1, end(*args_it))) {
					switch (c) {
					case 'h': arguments_.help(true); break;
					case 'd': arguments_.reverse(true); break;
					case 'r': arguments_.suppress_recursive(true); break;
					case 's': arguments_.sort_by_size(true); break;
					case 'v': arguments_.verbose(true); break;
					case 'b': arguments_.benchmark(true); break;
					case 'x':
						arguments_.regex(true);
						if (++args_it != end(args_deque)) {
							arguments_.regex_pattern(*args_it);
							break;
						}
						else {
							print(stderr, "Error: -x switch used without regular expression argument provided.\n");
							exit(EXIT_FAILURE);
						}
					}
				}
			}
			else {
                arguments_.dir_path(*(args_it++));
				break;
			}
		}

		if (args_it != end(args_deque) && !arguments_.help()) {
			print(stderr, "Error: Too many commandline arguments: {}...\n", *args_it);
			exit(EXIT_FAILURE);
		}
		else if (!filesystem::is_directory(arguments_.dir_path())) {
			print(stderr, "Error: The system cannot find the canonical file specified: \"{}\"\n", arguments_.dir_path());
			exit(EXIT_FAILURE);
		}
	}
}   // End of namespace fileusage
