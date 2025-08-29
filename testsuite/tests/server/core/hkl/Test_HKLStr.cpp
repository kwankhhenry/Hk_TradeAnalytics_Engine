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

TEST_F(HKLStrTest, AssignmentOperatorCopiesContent) {
    HKLStr<IChar> str1("assign");
    HKLStr<IChar> str2;
    str2 = str1;
    EXPECT_EQ(str2, str1);
}

TEST_F(HKLStrTest, AssignmentOperatorFromCString) {
    HKLStr<IChar> str;
    str = "assigned";
    EXPECT_EQ(str, "assigned");
}

TEST_F(HKLStrTest, AppendOperatorAddsContent) {
    HKLStr<IChar> str("foo");
    str += "bar";
    EXPECT_EQ(str, "foobar");
}

TEST_F(HKLStrTest, FormatCreatesFormattedString) {
    HKLStr<IChar> str;
    str.Format("Value: %d", 42);
    EXPECT_EQ(str, "Value: 42");
}

TEST_F(HKLStrTest, FormatStringStaticCreatesFormattedString) {
    auto str = HKLStr<IChar>::FormatString("Static: %s", "test");
    EXPECT_EQ(str, "Static: test");
}

TEST_F(HKLStrTest, SerializationToHKLBlkAndBack) {
    HKLStr<IChar> str("serialize");
    HKLBlk blk;
    str >> blk; // Serialize
    HKLStr<IChar> str2;
    str2 << blk; // Deserialize
    EXPECT_EQ(str2, str);
}

TEST_F(HKLStrTest, TrimLeftRemovesLeadingSpaces) {
    HKLStr<IChar> str("   left");
    str.TrimLeft(' ');
    EXPECT_EQ(str, "left");
}

TEST_F(HKLStrTest, TrimRightRemovesTrailingSpaces) {
    HKLStr<IChar> str("right   ");
    str.TrimRight(' ');
    EXPECT_EQ(str, "right");
}

TEST_F(HKLStrTest, TrimRemovesBothSides) {
    HKLStr<IChar> str("  both  ");
    str.Trim(' ');
    EXPECT_EQ(str, "both");
}

TEST_F(HKLStrTest, OperatorPlusConcatenatesStrings) {
    HKLStr<IChar> str1("foo");
    HKLStr<IChar> str2("bar");
    HKLStr<IChar> str3 = str1 + str2;
    EXPECT_EQ(str3, "foobar");
}

TEST_F(HKLStrTest, SetNoValueAndIsNoValue) {
    HKLStr<IChar> str("something");
    str.SetNoValue();
    EXPECT_TRUE(str.IsNoValue());
    EXPECT_EQ(str.size(), 0u);
}

TEST_F(HKLStrTest, CodesetSetAndGet) {
    HKLStr<IChar> str("abc");
    str.SetCodeset(HKL_CODESET_BIG5);
    EXPECT_EQ(str.GetCodeset(), HKL_CODESET_BIG5);
}

TEST_F(HKLStrTest, IsASCIISupersetTrueForUTF8) {
    HKLStr<IChar> str("abc");
    str.SetCodeset(HKL_CODESET_UTF_8);
    EXPECT_TRUE(str.IsASCIISuperset());
}

TEST_F(HKLStrTest, ComparisonOperators) {
    HKLStr<IChar> str1("abc");
    HKLStr<IChar> str2("def");
    EXPECT_TRUE(str1 < str2);
    EXPECT_TRUE(str2 > str1);
    EXPECT_TRUE(str1 <= str2);
    EXPECT_TRUE(str2 >= str1);
    EXPECT_TRUE(str1 != str2);
    EXPECT_TRUE(str1 == HKLStr<IChar>("abc"));
}

TEST_F(HKLStrTest, SubstrViewReturnsCorrectSubstring) {
    HKLStr<IChar> str("substring");
    auto view = str.substr_view(3, 3);
    EXPECT_EQ(view, "str");
}

TEST_F(HKLStrTest, ViewReturnsFullString) {
    HKLStr<IChar> str("fullview");
    auto view = str.view();
    EXPECT_EQ(view, "fullview");
}