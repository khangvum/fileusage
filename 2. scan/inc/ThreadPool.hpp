#pragma once
/*! \file	    ThreadPool.hpp
    \brief	    ThreadPool class declaration
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

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>	// std::function
#include <condition_variable>
#include <future>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace fileusage {
    class ThreadPool {
    public:
        using Task = std::function<void()>;
    private:
        std::vector<std::jthread> threads_;
        std::condition_variable condition_;
        std::condition_variable idle_condition_;
        std::mutex mtx_;
        bool stop_;
        std::size_t outstanding_tasks_;
        std::queue<Task> tasks_;

        void worker();
    public:
        // Constructor
        explicit ThreadPool(std::size_t thread_count = std::thread::hardware_concurrency());

        // Destructor
        ~ThreadPool();

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        // Wait until all queued and currently running tasks have completed.
        void wait_idle();

        // Method
        /*	\brief		Add a task to the queue
            \param		class T&&		- The task
                        class... Args&&	- The taks's arguments
            \return		std::future<std::invoke_result_t<T, Args...>> - The future object that will hold the result of the task
        */
        template<class T, class... Args>
        auto enqueue(T&& task, Args&&... args) -> std::future<std::invoke_result_t<T, Args...>> {
            using return_type = std::invoke_result_t<T, Args...>;
            auto wrapper{ std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<T>(task), std::forward<Args>(args)...)) };
            auto result{ wrapper->get_future() };
            {
                std::unique_lock<std::mutex> lock(mtx_);
                if (stop_)
                    throw std::runtime_error("cannot enqueue work on a stopped ThreadPool");
                ++outstanding_tasks_;
                tasks_.emplace([wrapper] { (*wrapper)(); });
            }
            condition_.notify_one();
            return result;
        }
    };
}	// End of namespace fileusage