/*! \file	    args.cpp
	\brief	    Function definitions for handling command line arguments
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

#include "../inc/args.hpp"
#include <print>
using namespace std;

namespace fileusage {
	void print_help() {
		print("\tUsage: fileusage [--help] [-hdrsv(x regularexpression)] [folder]\n"
			"\tswitches:\n"
			"\t\th\thelp\n"
			"\t\td\treverse the order of listing\n"
			"\t\tr\tsuppress recursion\n"
			"\t\ts\tsort by file sizes\n"
			"\t\tv\tverbose\n"
			"\t\tb\tbenchmark\n"
			"\t\tx\tfilter with a regular expression\n\n"
			"\tfolder\n"
			"\t\tstarting folder or current folder if not specified\n");
	}
}	// End of namespace fileusage