#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>

template<typename T>                // Note: Template class cannot split declaration and method definitions
class ThreadQueue{
private:
    std::queue<T> q;                // Underlying queue to store elements
    std::condition_variable cv;     // Condition variable for synchronization
    std::mutex mtx;                 // Mutex for exclusive access to queue
public:
    void push(T const& elem){
        std::lock_guard<std::mutex> lock(mtx);
        q.push(elem);
        cv.notify_one();            // Notify one waiting thread that data is available
    }

    T pop(){
        std::unique_lock<std::mutex> unLock(mtx);  
        cv.wait(unLock, [&] { return !q.empty(); });  // Wait until the queue is not empty
        T frontItem = q.front();                      
        q.pop();                                  
        return frontItem;     
    }

    T front(){
        return q.front();
    }

    bool empty(){
        return q.empty();
    }

    int size(){
        return q.size();
    }
};