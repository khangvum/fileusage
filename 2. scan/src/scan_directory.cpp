/*! \file	    scan_directory.cpp
	\brief	    Function definitions for scanning the directory
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

#include "../inc/scan_directory.hpp"
#include "../inc/ThreadPool.hpp"
#include <iostream>
#include <map>
#include <regex>
#include <filesystem>
#include <algorithm>
using namespace std;

namespace fileusage {
	void scan_directory(deque<Extension>& ext_deque, const Argument& arguments) {
		// Create a map to store the extensions and their information
		map<string, ExtensionInfo> ext_map;

		// Create the regex pattern
		regex regex_pattern(arguments.regex_pattern());

		// Create a ThreadPool & a mutex for synchronizing access to the ext_map
		ThreadPool pool;
		mutex mtx;

		// Lambda function to scan through the directory
		function<void(const filesystem::path&)> scan{ [&](const filesystem::path& dir) {
			for (const auto& entry : filesystem::directory_iterator(dir)) {
				try {
					if (is_directory(entry)) {
						if (!arguments.suppress_recursive()) {
							pool.enqueue(scan, entry);
						}
					}
					else if (is_regular_file(entry)) {
						string ext{ entry.path().extension().string() };
						if (!arguments.regex() || regex_match(ext, regex_pattern)) {
							lock_guard<mutex> lock(mtx);
							ext_map[ext].add_count(1);
							ext_map[ext].add_size(file_size(entry));

							if (arguments.verbose()) {
								try {
									ext_map[ext].add_path(entry.path().string());
								}
								catch (const exception&) {
									continue;
								}
							}
						}
					}
				}
				catch (const filesystem::filesystem_error&) {
					continue;
				}
			}
		} };

		// Load the extensions into the map
		scan(arguments.dir_path());

		// Wait for all threads to finish
		pool.~ThreadPool();

		// Load the deque from the map for sorting purposes
		for (const auto& ext : ext_map)
			ext_deque.emplace_back(ext.first, ext.second);
	}

	void sort_deque(deque<Extension>& ext_deque, const Argument& arguments) {
		if (arguments.sort_by_size()) {
			sort(begin(ext_deque), end(ext_deque), [](const Extension& lhs, const Extension& rhs) {
				return lhs.info().size() < rhs.info().size();
				});
		}

		if (arguments.reverse())
			reverse(begin(ext_deque), end(ext_deque));
	}
}	// End of namespace fileusage