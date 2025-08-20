#pragma once
/*! \file	    Extension.hpp
	\brief	    Extension class declaration
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

#include "ExtensionInfo.hpp"
#include <string>

namespace fileusage {
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
}	// End of namespace fileusage 