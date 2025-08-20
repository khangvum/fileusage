#pragma once
/*! \file	    summary.hpp
	\brief	    Function declarations for reporting the summary
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

#include "../../2. scan/inc/Extension.hpp"
#include "../../1. arguments/inc/Argument.hpp"
#include <string>
#include <deque>

namespace fileusage {
	/*	\brief		Print the summary: File extensions, their counts, and sizes
		\param		const std::deque<Extension>&	- The deque to store the file extensions
					const Argument&					- The Argument object
	*/
	void print_summary(const std::deque<Extension>& ext_deque, const Argument& arguments);
}	// End of namespace fileusage