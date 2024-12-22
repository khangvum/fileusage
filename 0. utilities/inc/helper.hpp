#pragma once
/*! \file	    helper.hpp
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

#include "../../2. scan/scan.hpp"
#include <sstream>
#include <string>
#include <iomanip>
#include <deque>

/*	\brief		Print the title of the program 
*/
void print_title();

/*	\brief		Print the header of each section
	\param		const std::string& - Title 
*/
void print_header(const std::string& title);

/*	\brief		Format a number
	\param		typename T	- The number to be formatted
				int			- The precision (Optional)
	\return		std::string	- The formatted number 
*/
template <typename T>
std::string format_number(T number, int precision = 0) {
	std::ostringstream os;
	(void)os.imbue(std::locale(""));

	if (precision == 0)
		os << number;
	else
		os << std::fixed << std::setprecision(precision) << number;

	return os.str();
}

 /*	\brief		Calculate the widths of the columns
	\param		const std::deque<Extension>&	- The deque to store the file extensions & their information
				std::streamsize&				- The width of the extension column
				std::streamsize&				- The width of the count column
				std::streamsize&				- The width of the size column
				size_t&							- The total counts
				std::streamsize&				- The total sizes
				size_t&							- The largest count
*/
void find_maxima(const std::deque<Extension>& ext_deque, std::streamsize& ext_width, std::streamsize& count_width, std::streamsize& size_width, size_t& total_counts, std::streamsize& total_sizes, size_t& largest_count);