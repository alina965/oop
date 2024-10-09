#pragma once
#include <string>
#include <vector>

/**
 * @class BitArray
 * @brief A class that represents a dynamic array of bits with various bitwise
 * operations.
 */
class BitArray {
public:
  /**
   * @brief Default constructor that creates an empty bit array.
   */
  BitArray();

  /**
   * @brief Destructor for the BitArray class.
   */
  ~BitArray();

  /**
   * @brief Constructs a bit array with a specified number of bits.
   *
   * @param[in] num_bits The number of bits to initialize in the bit array.
   * @param[in] value The initial value for the first sizeof(long) bits (default
   * is 0).
   *
   * @throw std::invalid_argument if number of bits is negative
   */
  explicit BitArray(int num_bits, unsigned long value = 0);

  /**
   * @brief Copy constructor that creates a new bit array by copying another.
   *
   * @param[in] b The bit array to copy.
   */
  BitArray(const BitArray &b);

  /**
   * @brief Swaps the contents of this bit array with another.
   *
   * @param[in] b The bit array to swap with.
   */
  void swap(BitArray &b);

  /**
   * @brief Assignment operator to copy another bit array into this one.
   *
   * @param[in] b The bit array to copy.
   * @return Reference to this bit array.
   */
  BitArray &operator=(const BitArray &b);

  /**
   * @brief Resizes the bit array.
   *
   * @param[in] num_bits The new size of the bit array.
   * @param[in] value The value to initialize new bits with (default is false).
   *
   * @throw std::invalid_argument if number of bits is negative
   */
  void resize(int num_bits, bool value = false);

  /**
   * @brief Clears the bit array.
   */
  void clear();

  /**
   * @brief Appends a new bit to the end of the bit array.
   *
   * @param bit[in] The value of the bit to add.
   */
  void push_back(bool bit);

  /**
   * @brief Performs a bitwise AND operation with another bit array.
   *
   * @param[in] b The bit array to AND with.
   * @return Reference to this bit array after modification.
   *
   * @throw throw std::invalid_argument if the sizes of the arrays are different
   */
  BitArray &operator&=(const BitArray &b);

  /**
   * @brief Performs a bitwise OR operation with another bit array.
   *
   * @param[in] b The bit array to OR with.
   * @return Reference to this bit array after modification.
   *
   * @throw throw std::invalid_argument if the sizes of the arrays are different
   */
  BitArray &operator|=(const BitArray &b);

  /**
   * @brief Performs a bitwise XOR operation with another bit array.
   *
   * @param[in] b The bit array to XOR with.
   * @return Reference to this bit array after modification.
   *
   * @throw throw std::invalid_argument if the sizes of the arrays are different
   */
  BitArray &operator^=(const BitArray &b);

  /**
   * @brief Left-shifts the bit array by `n` positions, filling with zeros.
   *
   * @param[in] n Number of positions to shift.
   * @return Reference to this bit array after the shift.
   *
   * @throw std::invalid_argument if index is negative
   */
  BitArray &operator<<=(int n);

  /**
   * @brief Right-shifts the bit array by `n` positions, filling with zeros.
   *
   * @param[in] n Number of positions to shift.
   * @return Reference to this bit array after the shift.
   *
   * @throw std::invalid_argument if index is negative
   */
  BitArray &operator>>=(int n);

  /**
   * @brief Left-shifts the bit array by `n` positions, filling with zeros.
   *
   * @param[in] n Number of positions to shift.
   * @return A new bit array with the shifted bits.
   */
  BitArray operator<<(int n) const;

  /**
   * @brief Right-shifts the bit array by `n` positions, filling with zeros.
   *
   * @param n Number of positions to shift.
   * @return A new bit array with the shifted bits.
   */
  BitArray operator>>(int n) const;

  /**
   * @brief Sets the bit at index `n` to the value `val`.
   *
   * @param[in] n The index of the bit to modify.
   * @param[in] val The value to set the bit to (default is true).
   * @return Reference to this bit array after modification.
   *
   * @throw std::out_of_range if index out of range
   */
  BitArray &set(int n, bool val = true);

  /**
   * @brief Sets all bits in the array to `true`.
   *
   * @return Reference to this bit array after modification.
   */
  BitArray &set();

  /**
   * @brief Resets the bit at index `n` to `false`.
   *
   * @param[in] n The index of the bit to reset.
   * @return Reference to this bit array after modification.
   *
   * @throw std::out_of_range if index out of range
   */
  BitArray &reset(int n);

  /**
   * @brief Resets all bits in the array to `false`.
   *
   * @return Reference to this bit array after modification.
   */
  BitArray &reset();

  /**
   * @brief Checks if any bit in the array is set to `true`.
   *
   * @return `true` if at least one bit is `true`, otherwise `false`.
   */
  bool any() const;

  /**
   * @brief Checks if all bits in the array are `false`.
   *
   * @return `true` if all bits are `false`, otherwise `false`.
   */
  bool none() const;

  /**
   * @brief Performs a bitwise inversion of the array.
   *
   * @return A new bit array with all bits inverted.
   */
  BitArray operator~() const;

  /**
   * @brief Accesses the value of the bit at index `i`.
   *
   * @param[in] i The index of the bit.
   * @return The value of the bit (true or false).
   *
   * @throw std::out_of_range if index out of range
   */
  bool operator[](int i) const;

  /**
   * @brief Counts the number of bits set to `true`.
   *
   * @return The number of `true` bits.
   */
  int count() const;

  /**
   * @brief Returns the number of bits in the array.
   *
   * @return The size of the bit array.
   */
  int size() const;

  /**
   * @brief Checks if the array is empty (contains no bits).
   *
   * @return `true` if the array is empty, otherwise `false`.
   */
  bool empty() const;

  /**
   * @brief Converts the bit array to a string representation.
   *
   * @return A string containing the bit array.
   */
  std::string to_string() const;

  /**
   * @brief Compares two bit arrays for equality.
   *
   * @param[in] a The first bit array.
   * @param[in] b The second bit array.
   * @return `true` if the arrays are equal, otherwise `false`.
   */
  friend bool operator==(const BitArray &a, const BitArray &b);

  /**
   * @brief Compares two bit arrays for inequality.
   *
   * @param a The first bit array.
   * @param b The second bit array.
   * @return `true` if the arrays are not equal, otherwise `false`.
   */
  friend bool operator!=(const BitArray &a, const BitArray &b);

private:
  int num_bits_; ///< The number of bits in the array.
  std::vector<unsigned long>
      bit_array_; ///< The underlying storage for the bits.
};

/**
 * @brief Performs a bitwise AND operation between two bit arrays.
 *
 * @param[in] b1 The first bit array.
 * @param[in] b2 The second bit array.
 * @return A new bit array containing the result.
 */
BitArray operator&(const BitArray &b1, const BitArray &b2);

/**
 * @brief Performs a bitwise OR operation between two bit arrays.
 *
 * @param[in] b1 The first bit array.
 * @param[in] b2 The second bit array.
 * @return A new bit array containing the result.
 */
BitArray operator|(const BitArray &b1, const BitArray &b2);

/**
 * @brief Performs a bitwise XOR operation between two bit arrays.
 *
 * @param[in] b1 The first bit array.
 * @param[in] b2 The second bit array.
 * @return A new bit array containing the result.
 */
BitArray operator^(const BitArray &b1, const BitArray &b2);
