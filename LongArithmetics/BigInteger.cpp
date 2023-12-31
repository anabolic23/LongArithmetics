﻿#include "BigInteger.h"

BigInteger::BigInteger() {
    for (int i = 0; i < SIZE; i++) {
        number[i] = 0;
    }
}

BigInteger::BigInteger(const std::string& hexValue) {
    uint32_t* hexArray = convertHexStringToNumber(hexValue);
    for (int i = 0; i < SIZE; i++) {
        number[i] = hexArray[i];
    }
}

uint32_t BigInteger::convertHexSymboToDigit(char c) {
    if (c >= '0' && c <= '9')
        return static_cast<uint32_t>(c - '0');
    else if (c >= 'a' && c <= 'f')
        return static_cast<uint32_t>(c - 'a' + 10);
    else if (c >= 'A' && c <= 'F')
        return static_cast<uint32_t>(c - 'A' + 10);

    return 0;
}

char BigInteger::convertDigitToHexSymbol(uint32_t i, bool isSmall) {
    if (i >= 0 && i < 10) {
        return static_cast<char>('0' + i);
    }
    else if (i >= 10 && i < 16) {
        if (isSmall) {
            return static_cast<char>('a' + i - 10);
        }
        else {
            return static_cast<char>('A' + i - 10);
        }
    }
    throw std::invalid_argument("Incorrect number");
}

uint32_t* BigInteger::convertHexStringToNumber(const std::string& str) {
    uint32_t* array = new uint32_t[SIZE](); // Initialize with zeros
    std::string strReverse(str.rbegin(), str.rend());
    int cell = -1;
    for (size_t i = 0; i < strReverse.length(); i++) {
        uint32_t j = static_cast<uint32_t>(i) % 8;
        if (j == 0) {
            cell++;
        }
        uint32_t powerOfTwo = static_cast<uint32_t>(1 << (4 * j));
        uint32_t hexSymbol = convertHexSymboToDigit(strReverse[i]);
        array[cell] += hexSymbol * powerOfTwo;
    }
    return array;
}

std::string BigInteger::convertNumberToHexString(uint32_t* array, bool isSmall) {
    std::string output;
    uint32_t* reverseArray = new uint32_t[SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        reverseArray[i] = array[SIZE - 1 - i];
    }

    for (int i = 0; i < SIZE; i++) {
        std::string str;
        for (int j = 0; j < 8; j++) {
            uint32_t powerOfTwo = static_cast<uint32_t>(1 << (4 * j));
            uint32_t temp = reverseArray[i] / powerOfTwo;
            temp = temp % 16;
            str += convertDigitToHexSymbol(temp, isSmall);
        }
        std::reverse(str.begin(), str.end());
        output += str;
    }
    size_t firstNonZero = output.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        output = output.substr(firstNonZero);
    }
    else {
        output = "0";
    }

    return output;
}

BigInteger BigInteger::operator + (const BigInteger& B) const {
    uint32_t carry = 0;
    BigInteger C;
    for (int i = 0; i < SIZE; i++) {
        uint64_t temp = static_cast<uint64_t>(number[i]) + static_cast<uint64_t>(B.number[i]) + carry;
        C.number[i] = static_cast<uint32_t>(temp & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temp >> 32);
    }
    return C;
}

BigInteger BigInteger::operator - (const BigInteger& B) const {
    uint32_t borrow = 0;
    BigInteger C;
    for (int i = 0; i < SIZE; i++) {
        int64_t temp = static_cast<int64_t>(number[i]) - static_cast<int64_t>(B.number[i]) - borrow;
        if (temp >= 0) {
            C.number[i] = static_cast<uint32_t>(temp);
            borrow = 0;
        }
        else {
            C.number[i] = static_cast<uint32_t>(0xFFFFFFFF + temp + 1);
            borrow = 1;
        }
    }
    if (borrow == 1) {
        throw std::exception("Error: The larger number is subtracted from the smaller one");
    }
    return C;
}

bool BigInteger::operator == (const BigInteger& B) const {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (number[i] != B.number[i]) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator != (const BigInteger& B) const {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (number[i] != B.number[i]) {
            return true;
        }
    }
    return false;
}

BigInteger BigInteger::operator * (const uint32_t b) const {
    uint32_t carry = 0;
    BigInteger C;
    for (int i = 0; i < SIZE; i++) {
        uint64_t temp = static_cast<uint64_t>(number[i]) * static_cast<uint64_t>(b) + static_cast<uint64_t>(carry);
        C.number[i] = static_cast<uint32_t>(temp & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temp >> 32);
    }
    C.number[SIZE - 1] = carry;
    return C;
}

BigInteger BigInteger::operator << (int b) const {
    BigInteger result(*this); // Create a copy of the current BigInteger

    // Perform a left shift for the internal data
    for (int i = SIZE - 1; i >= 0; i--) {
        if (i - b >= 0) {
            result.number[i] = result.number[i - b];
        }
        else {
            result.number[i] = 0; // Fill with zeros
        }
    }

    return result;
}

BigInteger BigInteger::operator >> (int b) const {
    BigInteger result(*this); // Create a copy of the current BigInteger

    // Perform a right shift for the internal data
    for (int i = 0; i < SIZE; i++) {
        if (i + b < SIZE) {
            result.number[i] = result.number[i + b];
        }
        else {
            result.number[i] = 0; // Fill with zeros
        }
    }

    return result;
}


bool BigInteger::operator < (const BigInteger& B) const {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (number[i] != B.number[i]) {
            return number[i] < B.number[i];
        }
    }
    return false;
}

bool BigInteger::operator > (const BigInteger& B) const {
    return B < *this;
}

bool BigInteger::operator <= (const BigInteger& B) const {
    for (int i = SIZE - 1; i >= 0; i--) {
        if (number[i] != B.number[i]) {
            return number[i] < B.number[i];
        }
    }
    return true;
}

bool BigInteger::operator >= (const BigInteger& B) const {
    return B <= *this;
}

BigInteger BigInteger::operator * (const BigInteger& B) const {
    BigInteger C;
    for (int i = 0; i < SIZE; i++) {
        BigInteger temp = *this * B.number[i];
        temp = temp << i;
        C = C + temp;
    }
    return C;
}

BigInteger BigInteger::square() const {
    return *this * *this;
}

int BigInteger::BitLength() const {
    int length = SIZE * 32; // Total number of bits
    for (int i = SIZE - 1; i >= 0; i--) {
        if (number[i] != 0) {
            int bitPos = 31;
            while (bitPos >= 0 && (number[i] & (1u << bitPos)) == 0) {
                bitPos--;
            }
            length = i * 32 + bitPos + 1;
            break;
        }
    }
    return length;
}

BigInteger BigInteger::LongShiftBitsToHigh(int bits) const {

    BigInteger result("0");

    if (bits <= 0) {
        return *this;
    }
    if (bits >= SIZE * 32) {
        return result;
    }

    int numBlocks = bits / 32; // Calculate the number of 32-bit blocks to shift
    int remainingBits = bits % 32; // Calculate the remaining bits to shift within a block

    uint32_t carry = 0;

    if (remainingBits != 0) {

        // Perform shifting for the blocks
        for (int i = 0; i < SIZE; i++) {
            result.number[i] = (this->number[i] << remainingBits) + carry;
            carry = (this->number[i] >> (32 - remainingBits));
        }

        // Shift the blocks
        for (int i = SIZE - 1; i >= numBlocks; i--) {
            result.number[i] = result.number[i - numBlocks];
        }

        // Fill lower blocks with zeros
        for (int i = 0; i < numBlocks; i++) {
            result.number[i] = 0;
        }
    }
    else {
        // Shift entire blocks of 32 bits to the left
        for (int i = SIZE - 1; i >= numBlocks; i--) {
            result.number[i] = this->number[i - numBlocks];
        }

        // Fill lower blocks with zeros
        for (int i = 0; i < numBlocks; i++) {
            result.number[i] = 0;
        }
    }

    return result;
}


BigInteger BigInteger::operator/(const BigInteger& other) const {
    if (other == BigInteger("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    if (*this < other) {
        return BigInteger("0");
    }

    BigInteger A = *this;
    BigInteger B = other;
    BigInteger Quotient;
    BigInteger Remainder;
    int k = B.BitLength();
    Remainder = A;
    Quotient = BigInteger("0");

    while (Remainder >= B) {
        int t = Remainder.BitLength();
        BigInteger C = B.LongShiftBitsToHigh(t - k);

        if (Remainder < C) {
            t = t - 1;
            C = B.LongShiftBitsToHigh(t - k);
        }

        Remainder = Remainder - C;
        Quotient = Quotient + BigInteger("1").LongShiftBitsToHigh(t - k);
    }

    return Quotient;
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    if (other == BigInteger("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    BigInteger A = *this;
    BigInteger B = other;
    BigInteger Remainder;
    int k = B.BitLength();
    Remainder = A;

    while (Remainder >= B) {
        int t = Remainder.BitLength();
        BigInteger C = B.LongShiftBitsToHigh(t - k);

        if (Remainder < C) {
            t = t - 1;
            C = B.LongShiftBitsToHigh(t - k);
        }

        Remainder = Remainder - C;
    }

    return Remainder;
}

BigInteger BigInteger::pow(const BigInteger& other) const {
    BigInteger base = *this;
    std::string exponent = convertIntoBinaryString(other);
    BigInteger result("1");

    for (int i = exponent.size() - 1; i >= 0; i--) {
        if (exponent[i] == '1')
            result = result * base;

        if (i > 0)
            base = base.square();
    }
    return result;
}

std::string BigInteger::convertIntoBinaryString(const BigInteger& other) const {
    std::string binaryString;

    for (int i = SIZE - 1; i >= 0; i--) {
        uint32_t currentNumber = other.number[i];

        for (int j = 31; j >= 0; j--) {
            uint32_t bit = (currentNumber >> j) & 1;
            binaryString += std::to_string(bit);
        }
    }

    binaryString.erase(0, binaryString.find_first_not_of('0'));


    if (binaryString.empty()) {
        return "0";
    }

    return binaryString;
}

BigInteger BigInteger::GenerateRandomBigInteger(int size = SIZE) {
    BigInteger randBigInt;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<uint32_t>    distr(0, UINT_MAX);

    for (int i = 0; i < size; ++i) {
        // Generate a random 32-bit unsigned integer
        uint32_t randomValue = static_cast<uint32_t>(distr(generator));

        // Assign the random value to the corresponding digit in the BigInteger
        randBigInt.number[i] = randomValue;
    }

    return randBigInt;
}

BigInteger BigInteger::shiftRight() {
    int carry = 0;
    BigInteger result("0");
    for (int i = SIZE - 1; i >= 0; --i) {
        result.number[i] = (this->number[i] >> 1) + (carry << 31);
        carry = this->number[i] & 1;
    }
    return result;
}

bool BigInteger::lastHexSymbolDivisibleByTwo() const {
    return (number[0] % 2 == 0);
}

BigInteger BigInteger::gcd(const BigInteger& a, const BigInteger& b) {
    if (b == BigInteger("0")) {
        return a;
    }

    BigInteger tempA = a;
    BigInteger tempB = b;
    BigInteger d("1");

    // Check for division by 2 using the last hex symbol
    while (tempA.lastHexSymbolDivisibleByTwo()) {
        if (tempB.lastHexSymbolDivisibleByTwo()) {
            tempA = tempA.shiftRight();
            tempB = tempB.shiftRight();
            d = d * BigInteger("2");
        }
        else {
            break;
        }
    }

    // Continue checking for division by 2 for tempA
    while (tempA.lastHexSymbolDivisibleByTwo()) {
        tempA = tempA.shiftRight();
    }

    // Euclidean algorithm to find GCD
    while (tempB != BigInteger("0")) {
        while (tempB.lastHexSymbolDivisibleByTwo()) {
            tempB = tempB.shiftRight();
        }
        BigInteger temp;
        if (tempA < tempB) {
            temp = tempA;
        }
        else {
            temp = tempB;
        }

        if (tempA < tempB) {
            tempB = tempB - tempA;
        }
        else {
            tempB = tempA - tempB;
        }
        tempA = temp;
    }

    d = d * tempA;
    return d;
}

BigInteger BigInteger::lcm(const BigInteger& a, const BigInteger& b) {
    BigInteger tempA = a;
    BigInteger tempB = b;

    return (tempA * tempB) / gcd(tempA, tempB);
}

BigInteger BigInteger::PreCalculation(const BigInteger& n) {
    int length = n.DigitLength();
    BigInteger Beta("1");
    Beta = Beta << (2 * length);
    BigInteger temp = Beta / n;
    return temp;
}

BigInteger BigInteger::BarrettReduction(const BigInteger& x, const BigInteger& n, const BigInteger& m) {
    int k = n.DigitLength();
    BigInteger tempX = x;
    BigInteger tempN = n;
    BigInteger tempM = m;

    if (tempX < tempN) {
        return tempX;
    }

    BigInteger Q = tempX >> (k - 1);
    Q = Q * tempM;
    Q = Q >> (k + 1);

    BigInteger R = tempX - (Q * tempN);
    while (R >= tempN) {
        R = R - tempN;
    }
    return R;
}

int BigInteger::DigitLength() const {
    int length = SIZE;
    while (number[length - 1] == 0)
    {
        length--;
        if (length == 0)
        {
            break;
        }
    }
    return length;
}

BigInteger BigInteger::AdditionMod(const BigInteger& a, const BigInteger& b, const BigInteger& m) {

    BigInteger result("0");
    result = a + b;

    if (result >= m) {
        result = BarrettReduction(result, m, PreCalculation(m));
    }

    return result;
}

BigInteger BigInteger::SubtractionMod(const BigInteger& a, const BigInteger& b, const BigInteger& m) {

    BigInteger result("0");

    if (a >= b) {
        result = a - b;
    }
    else {
        result = a + (m - b);
    }

    if (result >= m) {
        result = BarrettReduction(result, m, PreCalculation(m));
    }

    return result;
}

BigInteger BigInteger::MultiplicationMod(const BigInteger& a, const BigInteger& b, const BigInteger& m) {
    BigInteger result("0");

    result = a * b;

    if (result >= m) {
        result = BarrettReduction(result, m, PreCalculation(m));
    }

    return result;
}

BigInteger BigInteger::SquareMod(const BigInteger& a, const BigInteger& m) {
    return BigInteger::MultiplicationMod(a, a, m);
}

BigInteger BigInteger::LongModPowerBarrett(const BigInteger& a, const BigInteger& b, const BigInteger& n) {
    BigInteger result("1");
    BigInteger base = a % n;
    BigInteger Mu = PreCalculation(n);

    std::string binaryExp = b.convertIntoBinaryString(b);

    for (int i = binaryExp.length() - 1; i >= 0; --i) {
        if (binaryExp[i] == '1') {
            result = BarrettReduction(result * base, n, Mu);
        }
        base = BarrettReduction(base.square(), n, Mu);
    }
    return result;
}
