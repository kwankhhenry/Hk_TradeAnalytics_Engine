#pragma once

#ifndef TEST_HKLSTR_H
#define TEST_HKLSTR_H

#include "gtest/gtest.h"
#include "resource/testbase.h"

#include "hkl/HKLStr.h"

class HKLStrTest : public TestBase {
protected:
    HKLStr<IChar> str;

    void SetUp() override {
        // Optional: initialize or configure str if needed
    }

    void TearDown() override {
        // Optional: cleanup if needed
    }
};

#endif // TEST_HKLSTR_H