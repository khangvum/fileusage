/*! \file	    system.cpp
	\brief	    System utilities
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

#include "../inc/system.hpp"
using namespace std;

namespace fileusage {
	CONSOLE_SCREEN_BUFFER_INFO csbi{ 0 };
	UINT codepage{ GetConsoleOutputCP() };
	size_t horizontal_width{};

	// === 1. Color functions ======================================
	void save_color() { GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); }

	void set_color(WORD attribute) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attribute); }

	void restore_color() { set_color(csbi.wAttributes); }

	// === 2. Codepage functions ===================================
	void restore_codepage() { SetConsoleOutputCP(codepage); }
}	// End of namespace fileusage