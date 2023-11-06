#include "BigInteger.h"

BigInteger::BigInteger() {
    for (int i = 0; i < SIZE; i++) {
        number[i] = 0;
    }
}

BigInteger::BigInteger(const std::string& hexValue) {
    uint32_t* hexArray = HexStringIntoNumber(hexValue);
    for (int i = 0; i < SIZE; i++) {
        number[i] = hexArray[i];
    }
}

uint32_t BigInteger::HexSymbolIntoDigit(char c) {
    if (c >= '0' && c <= '9')
        return static_cast<uint32_t>(c - '0');
    else if (c >= 'a' && c <= 'f')
        return static_cast<uint32_t>(c - 'a' + 10);
    else if (c >= 'A' && c <= 'F')
        return static_cast<uint32_t>(c - 'A' + 10);

    return 0;
}

char BigInteger::DigitIntoHexSymbol(uint32_t i, bool isSmall) {
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

uint32_t* BigInteger::HexStringIntoNumber(const std::string& str) {
    uint32_t* array = new uint32_t[SIZE](); // Initialize with zeros
    std::string strReverse(str.rbegin(), str.rend());
    int cell = -1;
    for (size_t i = 0; i < strReverse.length(); i++) {
        uint32_t j = static_cast<uint32_t>(i) % 8;
        if (j == 0) {
            cell++;
        }
        uint32_t powerOfTwo = static_cast<uint32_t>(1 << (4 * j));
        uint32_t hexSymbol = HexSymbolIntoDigit(strReverse[i]);
        array[cell] += hexSymbol * powerOfTwo;
    }
    return array;
}

std::string BigInteger::NumberIntoHexString(uint32_t* array, bool isSmall) {
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
            str += DigitIntoHexSymbol(temp, isSmall);
        }
        std::reverse(str.begin(), str.end());
        output += str;
    }
    size_t firstNonZero = output.find_first_not_of('0');
    if (firstNonZero != std::string::npos) {
        output = output.substr(firstNonZero);
    }
    else {
        // Handle case when the string is empty or all zeros
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
    if (bits < 0) {
        throw std::invalid_argument("Shift bits must be non-negative.");
    }

    BigInteger result = *this;
    int wordShift = bits / 32;
    bits %= 32;

    // Shift words to the left
    for (int i = SIZE - 1; i >= wordShift; i--) {
        result.number[i] = result.number[i - wordShift];
    }
    for (int i = 0; i < wordShift; i++) {
        result.number[i] = 0;
    }

    // Shift bits within the words
    if (bits > 0) {
        int carry = 0;
        for (int i = SIZE - 1; i >= 0; i--) {
            uint32_t originalWord = result.number[i];
            result.number[i] = (originalWord << bits) | carry;
            carry = originalWord >> (32 - bits);
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
    BigInteger Q; // Quotient
    BigInteger R; // Remainder
    int k = B.BitLength();
    R = A;
    Q = BigInteger("0");

    while (R >= B) {
        int t = R.BitLength();
        BigInteger C = B.LongShiftBitsToHigh(t - k);

        if (R < C) {
            t = t - 1;
            C = B.LongShiftBitsToHigh(t - k);
        }

        R = R - C;
        Q = Q + BigInteger("1").LongShiftBitsToHigh(t - k);
    }

    return Q;
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    if (other == BigInteger("0")) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    BigInteger A = *this;
    BigInteger B = other;
    BigInteger R; // Remainder
    int k = B.BitLength();
    R = A;

    while (R >= B) {
        int t = R.BitLength();
        BigInteger C = B.LongShiftBitsToHigh(t - k);

        if (R < C) {
            t = t - 1;
            C = B.LongShiftBitsToHigh(t - k);
        }

        R = R - C;
    }

    return R;
}

BigInteger BigInteger::pow(const BigInteger& other) const {
    BigInteger base = *this;
    BigInteger exponent = other;
    BigInteger result("1");

    while (exponent != BigInteger("0")) {
        if ((exponent % BigInteger("2")) == BigInteger("1")) {
            result = result * base;
        }
        base = base.square();
        exponent = exponent / BigInteger("2");
    }

    return result;
}






