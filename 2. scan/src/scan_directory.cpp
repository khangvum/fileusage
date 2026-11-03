/*! \file	    scan_directory.cpp
    \brief	    Function definitions for scanning the directory
    \author	    Manh Khang Vu
    \date	    2024-12-03
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

#include "../inc/scan_directory.hpp"
#include "../inc/ThreadPool.hpp"
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

        // Directory tasks aggregate locally, then merge once to avoid locking per file.
        ThreadPool pool;
        mutex mtx;

        // Lambda function to scan through the directory
        function<void(const filesystem::path&)> scan{ [&](const filesystem::path& dir) {
            map<string, ExtensionInfo> local_map;
            error_code iterator_error;
            filesystem::directory_iterator entries{
                dir, filesystem::directory_options::skip_permission_denied, iterator_error
            };

            while (!iterator_error && entries != filesystem::directory_iterator{}) {
                const auto& entry{ *entries };
                error_code entry_error;
                const bool directory{ entry.is_directory(entry_error) };
                if (!entry_error && directory && !arguments.suppress_recursive()) {
                    pool.enqueue(scan, entry.path());
                }
                else if (!entry_error && entry.is_regular_file(entry_error)) {
                    const string ext{ entry.path().extension().string() };
                    if (!arguments.regex() || regex_match(ext, regex_pattern)) {
                        error_code size_error;
                        const auto size{ entry.file_size(size_error) };
                        if (!size_error) {
                            auto& info{ local_map[ext] };
                            info.add_count(1);
                            info.add_size(static_cast<streamsize>(size));
                            if (arguments.verbose())
                                info.add_path(entry.path().string());
                        }
                    }
                }

                entries.increment(iterator_error);
            }

            if (!local_map.empty()) {
                lock_guard<mutex> lock(mtx);
                for (auto& [extension, info] : local_map) {
                    auto& total{ ext_map[extension] };
                    total.add_count(info.count());
                    total.add_size(info.size());
                    if (arguments.verbose()) {
                        for (const auto& path : info.paths())
                            total.add_path(path);
                    }
                }
            }
        } };

        // Load the extensions into the map
        scan(arguments.dir_path());

        // Wait for all threads to finish
        pool.wait_idle();

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