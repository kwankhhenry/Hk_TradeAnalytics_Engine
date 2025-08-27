#pragma once

#ifndef TESTBASE_H
#define TESTBASE_H

#include <chrono>
#include "gtest/gtest.h"

class TestBase: public testing::Test{

private:
    // Declares the variables your tests want to use.
    std::chrono::_V2::system_clock::time_point start, stop;
    std::chrono::microseconds duration;

protected:  // You should make the members protected s.t. they can be accessed from sub-classes.
    
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() override {
        // Start the timer
        start = std::chrono::high_resolution_clock::now();
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    virtual void TearDown() {
        // Stop the timer
        stop = std::chrono::high_resolution_clock::now();

        // Calculate the duration
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        // Output the duration in microseconds
        //std::cout << "Time taken by code snippet: " << duration.count() << " microseconds" << std::endl;
    }
};

#endif // TESTBASE_H