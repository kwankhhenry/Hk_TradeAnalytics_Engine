#pragma once

#ifndef TEST_HKLSOCK_H
#define TEST_HKLSOCK_H

#include "gtest/gtest.h"
#include "resource/testbase.h"

#include "hkl/HKLSock.h"

class HKLSockTest : public TestBase {
protected:
    HKLSock sock;

    void SetUp() override {
        // Optional: initialize or configure sock if needed
    }

    void TearDown() override {
        // Optional: cleanup if needed
    }
};

#endif // TEST_HKLSOCK_H