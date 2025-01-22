#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>

#include "ThreadPool.h"
#include "ThreadQueue.h"

class ThreadPool;
class ThreadWorker{
    friend ThreadPool;
protected:
    ThreadWorker(ThreadPool* pool): thread_pool(pool){}
    void operator()();

private:
    ThreadPool* thread_pool;
};