#include "BitArray.h"
#include <algorithm>
#include <stdexcept>
#define BITS_PER_BLOCK (sizeof(unsigned long) * 8)

BitArray::BitArray() : num_bits_(0) { }

BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) : num_bits_(num_bits) {
    if (num_bits < 0) throw std::invalid_argument("Number of bits must be non-negative");
    bit_array_.resize((num_bits_ + BITS_PER_BLOCK - 1)/BITS_PER_BLOCK, 0UL);
    if (num_bits_ > 0) bit_array_[0] = value;
}

BitArray::BitArray(const BitArray &b) : num_bits_(b.num_bits_), bit_array_(b.bit_array_) { }

void BitArray::swap(BitArray& b) {
    std::swap(bit_array_, b.bit_array_);
    std::swap(num_bits_, b.num_bits_);
}

BitArray& BitArray::operator=(const BitArray& b) {
    num_bits_ = b.num_bits_;
    bit_array_ = b.bit_array_;
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) throw std::invalid_argument("Number of bits must be non-negative");
    bit_array_.resize((num_bits + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK, value ? ~0U : 0U); // инициализация блоков

    if (num_bits % BITS_PER_BLOCK != 0) { // инициализация битов по отдельности
        unsigned long mask = (~0UL << (num_bits_ % BITS_PER_BLOCK));
        if (value) {
            bit_array_[(num_bits + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK - 1] |= mask;
        } else {
            bit_array_[(num_bits + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK - 1] &= ~mask;
        }
    }
    num_bits_ = num_bits;
}

void BitArray::clear() {
    bit_array_.clear();
    num_bits_ = 0;
}

void BitArray::push_back(bool bit) {
    resize(num_bits_ + 1);
    set(num_bits_ - 1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) throw std::invalid_argument("Arrays must have the same size");
    for (int i = 0; i < bit_array_.size(); i++) {
        bit_array_[i] &= b.bit_array_[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) throw std::invalid_argument("Arrays must have the same size");
    for (int i = 0; i < bit_array_.size(); i++) {
        bit_array_[i] |= b.bit_array_[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) throw std::invalid_argument("Arrays must have the same size");
    for (int i = 0; i < bit_array_.size(); i++) {
        bit_array_[i] ^= b.bit_array_[i];
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) throw std::invalid_argument("Index must be non-negative");
    if (n >= num_bits_) {
        reset();
        return *this;
    }
    for (int i = 0; i < num_bits_ - n; i++) {
        set(i, (*this)[i + n]);
    }
    for (int i = num_bits_ - n; i < num_bits_; i++) {
        reset(i);
    }
    return *this;
}

BitArray & BitArray::operator<<=(int n) {
    if (n < 0) throw std::invalid_argument("Index must be non-negative");
    if (n >= num_bits_) {
        reset();
        return *this;
    }
    for (int i = num_bits_ - 1; i >= n; i--) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; i++) {
        reset(i);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) {
    if (n >= num_bits_ || n < 0) throw std::out_of_range("Index out of range");
    if (val) bit_array_[n / BITS_PER_BLOCK] |= (1UL << (n % BITS_PER_BLOCK));
    else bit_array_[n / BITS_PER_BLOCK] &= ~(1UL << (n % BITS_PER_BLOCK));
    return *this;
}

BitArray& BitArray::set() {
    for (auto & element : bit_array_) {
        element = ~0UL;
    }
    if (num_bits_ % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (num_bits_ % BITS_PER_BLOCK)) - 1;
        bit_array_[num_bits_ / BITS_PER_BLOCK] &= mask;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    if (n >= num_bits_ || n < 0) throw std::out_of_range("Index out of range");
    bit_array_[n / BITS_PER_BLOCK] &= ~(1UL << (n % BITS_PER_BLOCK));
    return *this;
}

BitArray& BitArray::reset() {
    fill(bit_array_.begin(), bit_array_.end(), 0UL);
    return *this;
}

bool BitArray::any() const {
    for (auto& element : bit_array_) {
        if (element) return true;
    }
    return false;
}

bool BitArray::none() const {
    for (auto& element : bit_array_) {
        if (element) return false;
    }
    return true;
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (auto& element : result.bit_array_) {
        element = ~element;
    }
    if (num_bits_ % BITS_PER_BLOCK != 0) {
        unsigned long mask = (1UL << (num_bits_ % BITS_PER_BLOCK)) - 1;
        result.bit_array_[(num_bits_ + BITS_PER_BLOCK - 1) / BITS_PER_BLOCK - 1] &= mask;
    }
    return result;
}

bool BitArray::operator[](int i) const {
    if (i >= num_bits_ || i < 0) throw std::out_of_range("Index out of range");
    return bit_array_[i / BITS_PER_BLOCK] & (1UL << (i % BITS_PER_BLOCK));
}

int BitArray::count() const {
    int result = 0;
    for (int i = 0; i < num_bits_; i++) {
        if ((*this)[i]) result++;
    }
    return result;
}

int BitArray::size() const {
    return num_bits_;
}

bool BitArray::empty() const {
    return num_bits_ == 0;
}

std::string BitArray::to_string() const {
    std::string result;
    for (int i = 0; i < num_bits_; i++) {
        result.push_back((*this)[i] ? '1' : '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bool operator==(const BitArray &a, const BitArray &b) {
    return ((a.num_bits_ == b.num_bits_) && (a.bit_array_ == b.bit_array_));
}

bool operator!=(const BitArray &a, const BitArray &b) {
    return !(a == b);
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    BitArray b3(b1);
    return b3 &= b2;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    BitArray b3(b1);
    return b3 |= b2;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    BitArray b3(b1);
    return b3 ^= b2;
}