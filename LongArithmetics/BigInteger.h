#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <random>
#include <bitset>
#include <cassert>

class BigInteger {
private:
    static const int SIZE = 256;
    uint32_t number[SIZE];

public:
    uint32_t* getNumber() {
        return number;
    }
    // Default constructor, creates a BigInteger with a value of 0
    BigInteger();

    // Constructor that takes an integer in hexadecimal format
    BigInteger(const std::string& hexValue);

    // Convert functions
    static uint32_t convertHexSymboToDigit(char c);
    static char convertDigitToHexSymbol(uint32_t i, bool isSmall = false);
    static uint32_t* convertHexStringToNumber(const std::string& str);
    static std::string convertNumberToHexString(uint32_t* array, bool isSmall = false);
    std::string convertIntoBinaryString(const BigInteger& other) const;

    // Addition and subtraction operations
    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;

    // Multiplication and square operations
    BigInteger operator*(const uint32_t other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger square() const;

    int BitLength() const;
    BigInteger LongShiftBitsToHigh(int bits) const;

    // Division and modulus operations
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;

    // Exponentiation operation
    BigInteger pow(const BigInteger& exponent) const;

    BigInteger operator >> (int b) const;
    BigInteger operator << (int b) const;

    // Comparison operators
    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;

    // Generator
    static BigInteger GenerateRandomBigInteger(int size);
    
};
