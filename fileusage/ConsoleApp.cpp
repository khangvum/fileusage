/*! \file	    ConsoleApp.cpp
	\brief	    Console singleton application base class definition
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

#include "ConsoleApp.hpp"
#include <print>
#include <stdexcept>
using namespace std;

namespace fileusage {
	ConsoleApp* ConsoleApp::this_app_{};

	ConsoleApp::ConsoleApp() {
		if (this_app_) {
			print(stderr, "Error: more than one instance of ConsoleApp.\n");
			exit(EXIT_FAILURE);
		}
		this_app_ = this;
	}
}	// End of namespace fileusage

int main(int argc, char* argv[]) try {
	// Install CRT memory system
#if defined(_DEBUG) && defined(_WIN32)
	int dbgFlags{ _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) };
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
#endif

	set_terminate([]() {
		print(stderr, "Unknown exception: terminating\n");
		exit(EXIT_FAILURE);
		});

	// Parse command line arguments
	fileusage::ConsoleApp::this_app_->args_.assign(argv, argv + argc);

	// Execute the application
	return fileusage::ConsoleApp::this_app_->execute();
}
catch (char const* msg) {
	print(stderr, "Error (main) caught exception string: {}\n", msg);
	return EXIT_FAILURE;
}
catch (logic_error& e) {
	print(stderr, "Error (main) caught logic_error: {}\n", e.what());
	return EXIT_FAILURE;
}
catch (runtime_error& e) {
	print(stderr, "Error (main) caught runtime_error: {}\n", e.what());
	return EXIT_FAILURE;
}
catch (exception& e) {
	print(stderr, "Error (main) caught exception: {}\n", e.what());
	return EXIT_FAILURE;
}
catch (...) {
	print(stderr, "Unknown exception: terminating\n");
	return EXIT_FAILURE;
}
