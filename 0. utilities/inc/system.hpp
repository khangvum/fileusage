#pragma once
/*! \file	    system.hpp
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

#include <Windows.h>
#undef min		// Remove <Windows.h> terrible min & max MACRO
#undef max

extern CONSOLE_SCREEN_BUFFER_INFO csbi;
extern UINT codepage;
extern size_t horizontal_width;

// === 1. Color functions ======================================
/*	\brief		Save the current color of the console
*/
void save_color();

/*	\brief		Set the color of the console
	\param		WORD - The attribute of the color
*/
void set_color(WORD attribute);

/*	\brief		Restore the color of the console
*/
void restore_color();

// === 2. Codepage functions ===================================
/*	\brief		Restore the original codepage after executing the program
*/
void restore_codepage();