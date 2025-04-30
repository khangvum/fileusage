/*! \file	    fileusage.cpp
    \brief	    File usage listing
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

#include "fileusage.hpp"
using namespace std;
using namespace fileusage;

int main(int argc, char* argv[])
{
    // Create a Argument object to parse the arguments
    Argument arguments;
    arguments.parse(argc, argv);

    // Print the title
    print_title();

    // If there is a help request, print the help message and exit
    if (arguments.help()) {
		print_help();
		return EXIT_SUCCESS;
	}

    // Else, begin the program by printing the folder path
    set_color(INVERSE_RED); cout << " Folder: ";
    set_color(RED); cout << " " << arguments.dir_path();
    set_color(WHITE); cout << "\n\n";

// === 1. Start time ===========================================
    auto start{ hour_clock::now() };

    // Scan through the directory and store the extensions' information in a deque
    deque<Extension> ext_deque;
    scan_directory(ext_deque, arguments);

// === 2. Scan time ============================================
    auto after_scan{ hour_clock::now() };

    // Sort the deque based on -s and -r switches
    sort_deque(ext_deque, arguments);

// === 3. Sort time ============================================
    auto after_sort{ hour_clock::now() };

    // Print the result to the console
    print_summary(ext_deque, arguments);

// === 2. Stop time ============================================
    auto stop{ hour_clock::now() };

    // If there is a benchmark request, print the benchmark
    if (arguments.benchmark()) {
        print_interval_times(start, after_scan, after_sort, stop);
    }
}