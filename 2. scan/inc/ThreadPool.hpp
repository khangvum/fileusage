#pragma once
/*! \file	    ThreadPool.hpp
	\brief	    ThreadPool class declaration
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

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>	// std::function
#include <condition_variable>
#include <future>

namespace fileusage {
	class ThreadPool {
	public:
		using Task = std::function<void()>;
	private:
		std::vector<std::jthread> threads_;
		std::condition_variable condition_;
		std::mutex mtx_;
		bool stop_;
		std::queue<Task> tasks;
	public:
		// Constructor
		explicit ThreadPool();

		// Destructor
		~ThreadPool();

		// Method
		/*	\brief		Add a task to the queue
			\param		class T&&		- The task
						class... Args&&	- The taks's arguments
			\return		std::future<std::invoke_result_t<T, Args...>> - The future object that will hold the result of the task
		*/
		template<class T, class... Args>
		auto enqueue(T&& task, Args&&... args) -> std::future<std::invoke_result_t<T, Args...>> {
			using return_type = std::invoke_result_t<T, Args...>;
			auto wrapper{ std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<T>(task), std::forward<Args>(args)...)) };
			{
				std::unique_lock<std::mutex> lock(mtx_);
				tasks.emplace([=] {
					(*wrapper)();
					});
			}
			condition_.notify_one();
			return wrapper->get_future();
		}
	};
}	// End of namespace fileusage