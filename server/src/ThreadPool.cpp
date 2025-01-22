#include <iostream>
#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int numThreads): 
                m_threads(numThreads), busy_threads(numThreads), shutdown_request(false)
{
    std::cout << "Initializing ThreadPool with " << numThreads << " threads.\n";
    for(unsigned int i = 0; i < m_threads; i++)
    {
        threads.emplace_back([this](){ThreadWorker(this)();});
    }
}

ThreadPool::~ThreadPool(){
  std::unique_lock<std::mutex> lock(mtx);
  std::cout << "Terminating ThreadPool." << std::endl;
  shutdown_request = true;
  lock.unlock();
  cv.notify_all();

  for(auto& th: threads)
  {
    th.join();
  }
}