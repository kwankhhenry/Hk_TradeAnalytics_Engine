#pragma once

#ifndef TEST_H
#define TEST_H

#include "gtest/gtest.h"
#include "resource/testbase.h"

#include "ThreadPool.h"

namespace ThreadTest{
    // Define fixture to test ThreadQueue and ThreadPool
    class ThreadPoolTest: public TestBase{

    protected: 
        void SetUp() override {
            // Optional: initialize or configure sock if needed
        }

        void TearDown() override {
            // Optional: cleanup if needed
        }

        // A helper function that some test uses.
        static int Func(int a)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            return a*a; 
        }
    };
} // Namespace

#endif // TEST_H