#pragma once
/*! \file	    Argument.hpp
	\brief	    Argument class declaration
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

#include <string>
#include <utility>
#include <filesystem>

/*! \def FILEUSAGE_PROPERTY(type, name)
	\brief Declares a private member name_, along with a public accessor and mutator
*/
#define FILEUSAGE_PROPERTY(type, name) \
private: \
	type name##_{}; \
public: \
	constexpr inline type const& name() const { return name##_; } \
	constexpr inline void name(type value) { name##_ = std::move(value); }

namespace fileusage {
	/*! \class	    Argument
		\brief	    Command line argument class
	*/
	class Argument {
		// Properties (each macro leaves the following members public)
		FILEUSAGE_PROPERTY(bool, help)
		FILEUSAGE_PROPERTY(bool, reverse)
		FILEUSAGE_PROPERTY(bool, suppress_recursive)
		FILEUSAGE_PROPERTY(bool, sort_by_size)
		FILEUSAGE_PROPERTY(bool, verbose)
		FILEUSAGE_PROPERTY(bool, benchmark)
		FILEUSAGE_PROPERTY(bool, regex)
		FILEUSAGE_PROPERTY(std::string, regex_pattern)
		FILEUSAGE_PROPERTY(std::string, dir_path)
	public:
		// Constructor
		Argument(bool h = false, bool d = false, bool r = false, bool s = false, bool v = false, bool b = false, bool x = false, const std::string& regex_pattern = "", const std::string& dir_path = std::filesystem::current_path().string())
			: help_{ h }, reverse_{ r }, suppress_recursive_{ d }, sort_by_size_{ s }, verbose_{ v }, benchmark_{ b }, regex_{ x }, regex_pattern_{ regex_pattern }, dir_path_{ dir_path } {}
	};
}	// End of namespace fileusage

// Keep the helper macro from leaking into other headers
#undef FILEUSAGE_PROPERTY