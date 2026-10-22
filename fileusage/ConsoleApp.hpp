#pragma once
/*! \file	    ConsoleApp.hpp
	\brief	    Console singleton application base class declaration
	\author	    Manh Khang Vu
	\date	    2026-10-22
	\copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

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

#include "fileusage.hpp"

#if defined(_WIN32)
#include <crtdbg.h>
#include <Windows.h>
#endif

#include <deque>
#include <string>

int main(int argc, char* argv[]);

namespace fileusage {
	/*! \class	    ConsoleApp
		\brief	    Base class for console singleton applications
	*/
	class ConsoleApp {
	protected:
		using CommandLineArgs = std::deque<std::string>;
	private:
		friend int ::main(int argc, char* argv[]);

		static ConsoleApp* this_app_;

		CommandLineArgs args_;
	protected:
		// Constructor
		ConsoleApp();

		// Accessors
		inline CommandLineArgs const& args() const { return args_; }

		// Methods
		virtual int execute() = 0;

		/*!	\brief	Parses the command line arguments.
			\return	A string containing the parsed arguments.
		*/
		[[nodiscard]] virtual Argument parse_arguments() = 0;
	};

	/*! \def	    MAKEAPP(name)
		\brief	    Macro to define a console application class
		\param	    name - The name of the application class
	*/
#define MAKEAPP(name)							\
    class name : public ConsoleApp				\
    {											\
        int execute() override;					\
        Argument parse_arguments() override;	\
    } name##_g;									\
    int name::execute()
}	// End of namespace fileusage