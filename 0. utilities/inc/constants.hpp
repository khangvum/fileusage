#pragma once
/*! \file	    constants.hpp
	\brief	    Useful constants
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

#include <Windows.h>

namespace fileusage {
	// === 1. Color constants ======================================
	//constexpr WORD GREY{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED };
	constexpr WORD WHITE{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY }; // FOREGROUND_INTENSITY | GREY
	constexpr WORD YELLOW{ FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY };
	constexpr WORD CYAN{ FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY };
	constexpr WORD GREEN{ FOREGROUND_GREEN | FOREGROUND_INTENSITY };
	constexpr WORD RED{ FOREGROUND_RED | FOREGROUND_INTENSITY };
	constexpr WORD INVERSE_WHITE{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY };
	constexpr WORD INVERSE_GREY{ BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED };
	constexpr WORD INVERSE_RED{ BACKGROUND_RED | BACKGROUND_INTENSITY };

	// === 2. Character constants in the codepage 850 ==============
	constexpr char copyright{ '\xB8' };
	constexpr char dash{ '\xC4' };
	constexpr char cross{ '\xC5' };
	constexpr char bar{ '\xB3' };
	constexpr char downward_T{ '\xC2' };
}	// End of namespace fileusage