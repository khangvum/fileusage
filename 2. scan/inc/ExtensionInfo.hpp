#pragma once
/*! \file	    ExtensionInfo.hpp
	\brief	    ExtensionInfo class declaration
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

#include <iostream>
#include <vector>

namespace fileusage {
	class ExtensionInfo {
		size_t count_;
		std::streamsize size_;
		std::vector<std::string> paths_;
	public:
		// Constructor
		ExtensionInfo(size_t count = 0, std::streamsize size = 0, std::vector<std::string> paths = {}) : count_(count), size_(size), paths_(paths) {}

		// Accessors
		constexpr inline size_t count() const { return count_; }
		constexpr inline std::streamsize size() const { return size_; }
		inline std::vector<std::string> paths() const { return paths_; }

		// Mutators
		constexpr inline void add_count(size_t count) { count_ += count; }
		constexpr inline void add_size(std::streamsize size) { size_ += size; }
		inline void add_path(const std::string& path) { paths_.emplace_back(path); }
	};
}	// End of namespace fileusage