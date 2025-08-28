#include "hkl/Test_HKLBlk.h"

TEST_F(HKLBlkTest, DefaultConstructorInitializesEmptyBuffer) {
    HKLBlk blk;
    EXPECT_EQ(blk.GetSize(), 0);
}

TEST_F(HKLBlkTest, AddAndPopBuffer) {
    const char data[] = "data";
    HKLBlk blk;
    blk.Add(data, sizeof(data));
    EXPECT_EQ(blk.GetSize(), sizeof(data));
    char out[10] = {};
    blk.Pop(out, sizeof(data));
    EXPECT_STREQ(out, data);
    EXPECT_EQ(blk.GetSize(), 0);
}

TEST_F(HKLBlkTest, AddValueAndPopValue) {
    HKLBlk blk;
    UInt32 value = 12345;
    blk.AddValue(value);
    UInt32 out = 0;
    EXPECT_TRUE(blk.PopValue(out));
    EXPECT_EQ(out, value);
}

TEST_F(HKLBlkTest, PeekDoesNotRemoveData) {
    HKLBlk blk;
    const char data[] = "peek";
    blk.Add(data, sizeof(data));
    char out[10] = {};
    blk.Peek(out, sizeof(data));
    EXPECT_STREQ(out, data);
    EXPECT_EQ(blk.GetSize(), sizeof(data));
}

TEST_F(HKLBlkTest, CutRemovesDataFromFront) {
    HKLBlk blk;
    const char data[] = "abcdef";
    blk.Add(data, sizeof(data));
    blk.Cut(3);
    EXPECT_EQ(blk.GetSize(), sizeof(data) - 3);
    char out[10] = {};
    blk.Pop(out, sizeof(data) - 3);
    EXPECT_STREQ(out, "def");
}