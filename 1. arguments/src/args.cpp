/*! \file	    args.cpp
	\brief	    Function definitions for handling command line arguments
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

#include "../inc/args.hpp"
#include <iostream>
using namespace std;

namespace fileusage {
	void print_help() {
		cout << "\tUsage: fileusage [--help] [-hdrsv(x regularexpression)] [folder]\n"s
			<< "\tswitches:\n"s
			<< "\t\th\thelp\n"s
			<< "\t\td\treverse the order of listing\n"s
			<< "\t\tr\tsuppress recursion\n"s
			<< "\t\ts\tsort by file sizes\n"s
			<< "\t\tv\tverbose\n"s
			<< "\t\tb\tbenchmark\n"s
			<< "\t\tx\tfilter with a regular expression\n\n"s
			<< "\tfolder\n"s
			<< "\t\tstarting folder or current folder if not specified\n"s;
	}
}	// End of namespace fileusage