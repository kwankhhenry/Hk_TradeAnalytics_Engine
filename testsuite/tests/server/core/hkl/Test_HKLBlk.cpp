#include "hkl/Test_HKLBlk.h"

TEST_F(HKLBlkTest, DefaultConstructorInitializesEmptyBuffer) {
    HKLBlk blk;
    EXPECT_EQ(blk.GetSize(), 0u);    // Initialize empty block expects empty size.
}

TEST_F(HKLBlkTest, AddAndPopBuffer) {
    const char data[] = "data";
    HKLBlk blk;
    blk.Add(data, sizeof(data));
    EXPECT_EQ(blk.GetSize(), sizeof(data));     // After adding data, size should match.

    char out[10] = {};
    blk.Pop(out, sizeof(data));
    EXPECT_STREQ(out, data);    // Data popped should match the original data.
    EXPECT_EQ(blk.GetSize(), 0u);    // After popping data, size should be empty.
}

TEST_F(HKLBlkTest, AddValueAndPopValue) {
    HKLBlk blk;
    UInt32 value = 12345;
    blk.AddValue(value);
    UInt32 out = 0;
    EXPECT_TRUE(blk.PopValue(out));     // Popping out = 12345.
    EXPECT_EQ(out, value);      // Popped value should match the original value.
}

TEST_F(HKLBlkTest, PeekDoesNotRemoveData) {
    HKLBlk blk;
    const char data[] = "peek";
    blk.Add(data, sizeof(data));
    char out[10] = {};
    blk.Peek(out, sizeof(data));
    EXPECT_STREQ(out, data);    // Peeked data out = "peek" should match the original data.
    EXPECT_EQ(blk.GetSize(), sizeof(data));    // Blk Size = 4 should remain unchanged.
}

TEST_F(HKLBlkTest, CutRemovesDataFromFront) {
    HKLBlk blk;
    const char data[] = "abcdef";
    blk.Add(data, sizeof(data));
    blk.Cut(3);
    EXPECT_EQ(blk.GetSize(), sizeof(data) - 3);     // Expect blk size = 3 now.
    char out[10] = {};
    blk.Pop(out, sizeof(data) - 3);     // Pop remaining data, out = "def"
    EXPECT_STREQ(out, "def");       // Data popped should match the original data.
}