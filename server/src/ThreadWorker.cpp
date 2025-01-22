#include "ThreadWorker.h"

void ThreadWorker::operator()(){
    // Each working thread starts by aquiring a lock and then awaits for condition_variable cv.
    std::unique_lock<std::mutex> lock(thread_pool->mtx);
    std::function<void()> task;

    // In case of spurious wake of the thread, but with stop flag set, return and exit thread.
    while (!thread_pool->shutdown_request || (thread_pool->shutdown_request && !thread_pool->tasksQueue.empty())){
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - Idle" << std::endl;
            thread_pool->busy_threads--;
            thread_pool->cv.wait(lock, [this] {
                return !thread_pool->tasksQueue.empty() || thread_pool->shutdown_request;
            });

            // Worker thread goes to work, if Queue is not empty then clear queue, otherwise do nothing
            if(!this->thread_pool->tasksQueue.empty()){
                std::cout << "Thread ID: " << std::this_thread::get_id() << " - Busy" << std::endl;
                thread_pool->busy_threads++;
                task = std::move(thread_pool->tasksQueue.front());
                thread_pool->tasksQueue.pop();
                lock.unlock();
                task();
                lock.lock();
            }
    } // Exit while loop when receive shutdown request
}