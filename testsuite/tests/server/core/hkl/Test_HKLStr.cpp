#include "hkl/Test_HKLStr.h"

TEST_F(HKLStrTest, DefaultConstructorInitializesEmptyString) {
    HKLStr<IChar> str;
    EXPECT_EQ(str.size(), 0u);
}

TEST_F(HKLStrTest, ConstructFromCString) {
    HKLStr<IChar> str("hello");
    EXPECT_EQ(str, "hello");
}

TEST_F(HKLStrTest, CopyConstructorCopiesContent) {
    HKLStr<IChar> str1("abc");
    HKLStr<IChar> str2(str1);
    EXPECT_EQ(str2, str1);
}

TEST_F(HKLStrTest, MoveConstructorTransfersContent) {
    HKLStr<IChar> str1("move");
    HKLStr<IChar> str2(std::move(str1));
    EXPECT_EQ(str2, "move");
}

TEST_F(HKLStrTest, OperatorPlusConcatenatesStrings) {
    HKLStr<IChar> str1("foo");
    HKLStr<IChar> str2("bar");
    HKLStr<IChar> str3 = str1 + str2;
    EXPECT_EQ(str3, "foobar");
}

TEST_F(HKLStrTest, SerializationToHKLBlkAndBack) {
    HKLStr<IChar> str("serialize");
    HKLBlk blk;
    str >> blk; // Serialize
    HKLStr<IChar> str2;
    str2 << blk; // Deserialize
    EXPECT_EQ(str2, str);
}