#pragma once
/*! \file	    scan_directory.hpp
	\brief	    Function declarations for scanning the directory
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

#include "Extension.hpp"
#include "../../1. arguments/arguments.hpp"
#include <deque>

 /*	\brief		Scan through the file directory
	\param		std::deque<Extension>&	- The deque to store the file extensions
				Argument&				- The argument object
*/
void scan_directory(std::deque<Extension>& ext_deque, const Argument& arguments);

/*	\brief		Sort the Extension deque based on the arguments
	\param		std::deque<Extension>&	- The deque to store the file extensions
				Argument&				- The argument object
*/
void sort_deque(std::deque<Extension>& ext_deque, const Argument& arguments);