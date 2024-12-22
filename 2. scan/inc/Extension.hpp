#pragma once
/*! \file	    Extension.hpp
	\brief	    Extension class declaration
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

#include "ExtensionInfo.hpp"
#include <string>

class Extension {
	std::string extension_;
	ExtensionInfo info_;
public:
	// Constructor
	Extension(const std::string& extension = "", const ExtensionInfo& info = {}) : extension_{ extension }, info_{ info } {}

	// Accessors
	inline std::string extension() const { return extension_; }
	inline ExtensionInfo info() const { return info_; }
};