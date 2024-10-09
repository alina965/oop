#include <gtest/gtest.h>
#include "BitArray.h"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray bit_array;
    ASSERT_EQ(bit_array.size(), 0);
    ASSERT_TRUE(bit_array.empty());
}

TEST(BitArrayTest, ParameterizedConstructor) {
    BitArray bit_array(9, 9);
    ASSERT_EQ(bit_array.size(), 9);
    ASSERT_EQ(bit_array.to_string(), "000001001");
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(bit_array1);
    ASSERT_EQ(bit_array1.size(), bit_array2.size());
    ASSERT_EQ(bit_array1.to_string(), bit_array2.to_string());
}

TEST(BitArrayTest, Swap) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(12, 4);
    bit_array1.swap(bit_array2);
    ASSERT_EQ(bit_array1.size(), 12);
    ASSERT_EQ(bit_array1.to_string(), "000000000100");
    ASSERT_EQ(bit_array2.size(), 9);
    ASSERT_EQ(bit_array2.to_string(), "000001001");
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2 = bit_array1;
    ASSERT_EQ(bit_array1.size(), bit_array2.size());
    ASSERT_EQ(bit_array1.to_string(), bit_array2.to_string());
}

TEST(BitArrayTest, ResizeLess) {
    BitArray bit_array(9, 9);
    bit_array.resize(7);
    ASSERT_EQ(bit_array.size(), 7);
    ASSERT_EQ(bit_array.to_string(), "0001001");
}

TEST(BitArrayTest, ResizeGreaterTrue) {
    BitArray bit_array(9, 9);
    bit_array.resize(10, true);
    ASSERT_EQ(bit_array.size(), 10);
    ASSERT_EQ(bit_array.to_string(), "1000001001");
}

TEST(BitArrayTest, ResizeGreaterFalse) {
    BitArray bit_array(9, 9);
    bit_array.resize(10);
    ASSERT_EQ(bit_array.size(), 10);
    ASSERT_EQ(bit_array.to_string(), "0000001001");
}

TEST(BitArrayTest, ResizeNegative) {
    BitArray bit_array(9, 9);
    ASSERT_THROW(bit_array.resize(-1), std::invalid_argument);
}

TEST(BitArrayTest, Clear) {
    BitArray bit_array(9, 9);
    bit_array.clear();
    ASSERT_EQ(bit_array.size(), 0);
    ASSERT_TRUE(bit_array.empty());
}

TEST(BitArrayTest, PushBack) {
    BitArray bit_array;
    bit_array.push_back(true);
    ASSERT_EQ(bit_array.size(), 1);
    ASSERT_EQ(bit_array[0], 1);
    bit_array.push_back(false);
    ASSERT_EQ(bit_array.size(), 2);
    ASSERT_EQ(bit_array[1], 0);
}

TEST(BitArrayTest, BitwiseOperationAnd) {
    BitArray bit_array1(9, 66);
    BitArray bit_array2(9, 99);
    bit_array1 &= bit_array2;
    ASSERT_EQ(bit_array1.to_string(), "001000010");
}

TEST(BitArrayTest, BitwiseOperationAndDifferentSizes) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(10, 5);
    ASSERT_THROW(bit_array1 &= bit_array2, std::invalid_argument);
}

TEST(BitArrayTest, BitwiseOperationOr) {
    BitArray bit_array1(9, 66);
    BitArray bit_array2(9, 99);
    bit_array1 |= bit_array2;
    ASSERT_EQ(bit_array1.to_string(), "001100011");
}

TEST(BitArrayTest, BitwiseOperationOrDifferentSizes) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(10, 5);
    ASSERT_THROW(bit_array1 |= bit_array2, std::invalid_argument);
}

TEST(BitArrayTest, BitwiseOperationXor) {
    BitArray bit_array1(9, 66);
    BitArray bit_array2(9, 99);
    bit_array1 ^= bit_array2;
    ASSERT_EQ(bit_array1.to_string(), "000100001");
}

TEST(BitArrayTest, BitwiseOperationXorDifferentSizes) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(10, 5);
    ASSERT_THROW(bit_array1 ^= bit_array2, std::invalid_argument);
}

TEST(BitArrayTest, LeftShift) {
    BitArray bit_array(9, 9);
    bit_array <<= 2;
    ASSERT_EQ(bit_array.to_string(), "000100100");
    bit_array = bit_array << 1;
    ASSERT_EQ(bit_array.to_string(), "001001000");
    bit_array <<= 9;
    ASSERT_EQ(bit_array.to_string(), "000000000");
}

TEST(BitArrayTest, RightShift) {
    BitArray bit_array(9, 9);
    bit_array >>= 2;
    ASSERT_EQ(bit_array.to_string(), "000000010");
    bit_array = bit_array >> 1;
    ASSERT_EQ(bit_array.to_string(), "000000001");
    bit_array >>= 9;
    ASSERT_EQ(bit_array.to_string(), "000000000");
}

TEST(BitArrayTest, SetBitTrue) {
    BitArray bit_array(9, 9);
    bit_array.set(1);
    ASSERT_EQ(bit_array.to_string(), "000001011");
}

TEST(BitArrayTest, SetBitFalse) {
    BitArray bit_array(9, 9);
    bit_array.set(0, false);
    ASSERT_EQ(bit_array.to_string(), "000001000");
}

TEST(BitArrayTest, SetOutOfBounds) {
    BitArray bit_array(9, 9);
    ASSERT_THROW(bit_array.set(10), std::out_of_range);
}

TEST(BitArrayTest, Set) {
    BitArray bit_array(9, 9);
    bit_array.set();
    ASSERT_EQ(bit_array.to_string(), "111111111");
}

TEST(BitArrayTest, ResetBit) {
    BitArray bit_array(9, 9);
    bit_array.reset(0);
    ASSERT_EQ(bit_array.to_string(), "000001000");
}

TEST(BitArrayTest, ResetOutOfBounds) {
    BitArray bit_array(9, 9);
    ASSERT_THROW(bit_array.reset(10), std::out_of_range);
}

TEST(BitArrayTest, Reset) {
    BitArray bit_array(9, 9);
    bit_array.reset();
    ASSERT_EQ(bit_array.to_string(), "000000000");
}

TEST(BitArrayTest, Any) {
    BitArray bit_array(9, 9);
    ASSERT_TRUE(bit_array.any());
    bit_array.reset();
    ASSERT_FALSE(bit_array.any());
}

TEST(BitArrayTest, None) {
    BitArray bit_array(9, 9);
    ASSERT_FALSE(bit_array.none());
    bit_array.reset();
    ASSERT_TRUE(bit_array.none());
}

TEST(BitArrayTest, BitwiseOperationNot) {
    BitArray bit_array(9, 9);
    bit_array = ~bit_array;
    ASSERT_EQ(bit_array.to_string(), "111110110");
}

TEST(BitArrayTest, AccessOutOfBounds) {
    BitArray bit_array(9, 9);
    ASSERT_THROW(bit_array[10], std::out_of_range);
}

TEST(BitArrayTest, Count) {
    BitArray bit_array(9, 9);
    ASSERT_EQ(bit_array.count(), 2);
}

TEST(BitArrayTest, EqualityOperators) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(12, 4);
    BitArray copy1 = bit_array1;
    ASSERT_TRUE(bit_array1 != bit_array2);
    ASSERT_FALSE(bit_array1 == bit_array2);
    ASSERT_TRUE(bit_array1 == copy1);
    ASSERT_FALSE(bit_array1 != copy1);
}

TEST(BitArrayTest, BitwiseOperations) {
    BitArray bit_array1(9, 9);
    BitArray bit_array2(9, 5);
    BitArray bit_array3;
    bit_array3 = bit_array1 & bit_array2;
    ASSERT_EQ(bit_array3.to_string(), "000000001");
    bit_array3 = bit_array1 | bit_array2;
    ASSERT_EQ(bit_array3.to_string(), "000001101");
    bit_array3 = bit_array1 ^ bit_array2;
    ASSERT_EQ(bit_array3.to_string(), "000001100");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}