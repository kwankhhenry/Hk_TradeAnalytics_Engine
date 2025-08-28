#pragma once

#ifndef TEST_HKLBLK_H
#define TEST_HKLBLK_H

#include "gtest/gtest.h"
#include "resource/testbase.h"

#include "hkl/HKLBlk.h"

class HKLBlkTest : public TestBase {
protected:
    HKLBlk blk;

    void SetUp() override {
        // Optional: initialize or configure blk if needed
    }

    void TearDown() override {
        // Optional: cleanup if needed
    }
};

#endif // TEST_HKLBLK_H