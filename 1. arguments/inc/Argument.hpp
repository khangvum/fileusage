#pragma once
/*! \file	    Argument.hpp
	\brief	    Argument class declaration
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

#include <string>
#include <filesystem>

namespace fileusage {
	class Argument {
		bool help_;
		bool reverse_;
		bool suppress_recursive_;
		bool sort_by_size_;
		bool verbose_;
		bool benchmark_;
		bool regex_;
		std::string regex_pattern_;
		std::string dir_path_;
	public:
		// Constructor
		Argument(bool h = false, bool d = false, bool r = false, bool s = false, bool v = false, bool b = false, bool x = false, const std::string& regex_pattern = "", const std::string& dir_path = std::filesystem::current_path().string()) : help_{ h }, reverse_{ r }, suppress_recursive_{ s }, sort_by_size_{ s }, verbose_{ v }, benchmark_{ b }, regex_{ x }, regex_pattern_{ regex_pattern }, dir_path_{ dir_path } {}

		// Accessors
		constexpr inline bool help() const { return help_; }
		constexpr inline bool reverse() const { return reverse_; }
		constexpr inline bool suppress_recursive() const { return suppress_recursive_; }
		constexpr inline bool sort_by_size() const { return sort_by_size_; }
		constexpr inline bool verbose() const { return verbose_; }
		constexpr inline bool benchmark() const { return benchmark_; }
		constexpr inline bool regex() const { return regex_; }
		inline std::string regex_pattern() const { return regex_pattern_; }
		inline std::string dir_path() const { return dir_path_; }

		// Method
		/*	\brief		Parse the command line arguments
			\param		int		- The count of the arguments
						char*	- The pointer to the arguments
		*/
		void parse(int argc, char* argv[]);
	};
}	// End of namespace fileusage