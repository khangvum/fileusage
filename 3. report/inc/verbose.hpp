#pragma once
/*! \file	    verbose.hpp
	\brief	    Function declarations for reporting the verbose
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

#include "../../2. scan/inc/Extension.hpp"
#include <deque>

namespace fileusage {
	/*	\brief		Print the absolute path of the file
		\param		const std::string&	- The path
					std::streamsize		- The width of the count
	*/
	void print_path(const std::string& path, std::streamsize count_width);

	/*	\brief		Print the verbose: File extensions, their counts, sizes, and absolute paths
		\param		const std::deque<Extension>&	- The deque to store the file extensions
					size_t							- The largest file extension count
	*/
	void print_verbose(const std::deque<Extension>& ext_deque, size_t largest_count);
}	// End of namespace fileusage