#pragma once
/*! \file	    args.hpp
	\brief	    Function declarations for handling command line arguments
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

/*	\brief		Print the help message if there is a -h or --help switch
*/
void print_help();