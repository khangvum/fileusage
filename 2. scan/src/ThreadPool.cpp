/*! \file	    ThreadPool.cpp
	\brief	    ThreadPool class definition
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

#include "../inc/ThreadPool.hpp"
using namespace std;

namespace fileusage {
	// Constructor
	ThreadPool::ThreadPool() : stop_(false) {
		size_t num_threads{ thread::hardware_concurrency() };
		for (size_t i{ 0 }; i < num_threads; ++i) {
			threads_.emplace_back([=] {
				while (true) {
					Task task;

					{
						// Lock the mutex
						unique_lock<mutex> lock(mtx_);
						condition_.wait(lock, [=] { return stop_ || !tasks.empty(); });

						// Check if there is a stop request & the task queue is empty
						if (stop_ && tasks.empty())
							break;

						// Get the task
						task = move(tasks.front());
						tasks.pop();
					}

					task();
				}
				});
		}
	}

	// Destructor
	ThreadPool::~ThreadPool() {
		{
			unique_lock<mutex> lock(mtx_);
			stop_ = true;
		}
		condition_.notify_all();

		for (auto& t : threads_)
			t.join();
	}
}	// End of namespace fileusage