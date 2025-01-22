#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <future>

#include "ThreadQueue.h"
#include "ThreadWorker.h"

class ThreadPool{
  private:
    unsigned int m_threads;
    std::vector<std::thread> threads;
    mutable std::mutex mtx;
    std::condition_variable cv;

    int busy_threads;
    bool shutdown_request;

    ThreadQueue<std::function<void()>> tasksQueue;    // Task Queue from ThreadQueue class
  public:
    friend class ThreadWorker;

    ThreadPool():ThreadPool(std::thread::hardware_concurrency()){};
    ThreadPool(unsigned int numThreads);
    ~ThreadPool();

    int QueueItems(){
        return tasksQueue.size();
    }

    template<class F, class... Args>
    auto PushTask(F&& f, Args&&... args)-> std::future<decltype(f(args...))>
    {
        // Create a function with bounded parameters ready to execute
        auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        // Encapsulate it into a shared ptr in order to be able to copy construct the task
        using return_type = decltype(f(args...));
        auto task_ptr = std::make_shared<std::packaged_task<return_type()>>(func);

        // Wrap the task pointer into a void lamdas
        auto wrapper_func = [task_ptr]()-> void {(*task_ptr)();};

        // Protects tasks queue from multiple access
        std::unique_lock<std::mutex>lock(mtx);
        tasksQueue.push(wrapper_func);
        lock.unlock();
        cv.notify_one();

        // Return future from promise
        return task_ptr->get_future();
    }
};