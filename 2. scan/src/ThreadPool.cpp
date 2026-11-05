/*! \file	    ThreadPool.cpp
    \brief	    ThreadPool class definition
    \author	    Manh Khang Vu
    \date	    2024-12-03
    \copyright	Manh Khang Vu

  =============================================================
  Revision History
  -------------------------------------------------------------

  Version 2026.10.23
      Updated for C++23
      Improved ThreadPool synchronization

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

#include "../inc/ThreadPool.hpp"
#include <algorithm>
using namespace std;

namespace fileusage {
    // Constructor
    ThreadPool::ThreadPool(size_t thread_count) : stop_(false), outstanding_tasks_(0) {
        thread_count = max<size_t>(1, thread_count);
        threads_.reserve(thread_count);
        for (size_t i{ 0 }; i < thread_count; ++i)
            threads_.emplace_back([this] { worker(); });
    }

    // Destructor
    ThreadPool::~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx_);
            stop_ = true;
        }
        condition_.notify_all();
    }

    void ThreadPool::wait_idle() {
        unique_lock<mutex> lock(mtx_);
        idle_condition_.wait(lock, [this] {
            return outstanding_tasks_ == 0;
            });
    }

    void ThreadPool::worker() {
        while (true) {
            Task task;
            {
                unique_lock<mutex> lock(mtx_);
                condition_.wait(lock, [this] {
                    return stop_ || !tasks_.empty();
                    });

                if (stop_ && tasks_.empty())
                    return;

                task = move(tasks_.front());
                tasks_.pop();
            }

            task();

            {
                lock_guard<mutex> lock(mtx_);
                --outstanding_tasks_;
                if (outstanding_tasks_ == 0)
                    idle_condition_.notify_all();
            }
        }
    }
}	// End of namespace fileusage