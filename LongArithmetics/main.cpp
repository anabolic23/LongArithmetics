#include <iostream>
#include "BigInteger.h"
#include <chrono>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate two random BigIntegers
    BigInteger a = BigInteger::GenerateRandomBigInteger(20);
    BigInteger b = BigInteger::GenerateRandomBigInteger(10);
    BigInteger t("5");

    std::cout << "a = " << BigInteger::convertNumberToHexString(a.getNumber()) << std::endl;
    std::cout << "b = " << BigInteger::convertNumberToHexString(b.getNumber()) << std::endl;
    std::cout << "t = " << BigInteger::convertNumberToHexString(t.getNumber()) << std::endl;

   
    // Perform arithmetic operations
    BigInteger c = a + b;
    BigInteger d = a - b;
    BigInteger e = a * 0x10;
    BigInteger f = a * b;
    BigInteger g = a.square();
    BigInteger h = a / b;
    BigInteger j = a % b;
    BigInteger k = a.pow(t); 
   
    const int iterations = 100;

    // Average time for addition
    long long totalTimeAddition = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger c = a + b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeAddition += duration.count();
    }
    double averageTimeAddition = static_cast<double>(totalTimeAddition) / iterations;
    std::cout << "Average time for addition: " << averageTimeAddition << " microseconds\n";

    // Average time for subtraction
    long long totalTimeSubtraction = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger d = a - b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeSubtraction += duration.count();
    }
    double averageTimeSubtraction = static_cast<double>(totalTimeSubtraction) / iterations;
    std::cout << "Average time for subtraction: " << averageTimeSubtraction << " microseconds\n";

    // Average time for multiplication (constant)
    long long totalTimeMultiplication = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger e = a * 0x10;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeMultiplication += duration.count();
    }
    double averageTimeMultiplication = static_cast<double>(totalTimeMultiplication) / iterations;
    std::cout << "Average time for multiplication (constant): " << averageTimeMultiplication << " microseconds\n";

    // Average time for big multiplication 
    long long totalTimeBigMultiplication = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger f = a * b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeBigMultiplication += duration.count();
    }
    double averageTimeBigMultiplication = static_cast<double>(totalTimeBigMultiplication) / iterations;
    std::cout << "Average time for big multiplication : " << averageTimeBigMultiplication << " microseconds\n";

    // Average time for square 
    long long totalTimeSquare = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger g = a.square();
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeSquare += duration.count();
    }
    double averagetotalTimeSquare = static_cast<double>(totalTimeSquare) / iterations;
    std::cout << "Average time for square : " << averagetotalTimeSquare << " microseconds\n";

    // Average time for division
    long long totalTimeDivision = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger h = a / b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeDivision += duration.count();
    }
    double averagetotalTimeDivision = static_cast<double>(totalTimeDivision) / iterations;
    std::cout << "Average time for division : " << averagetotalTimeDivision << " microseconds\n";

    // Average time for mod
    long long totalTimeMod = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger j = a % b;
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimeMod += duration.count();
    }
    double averagetotalTimeMod = static_cast<double>(totalTimeMod) / iterations;
    std::cout << "Average time for mod : " << averagetotalTimeMod << " microseconds\n";

    // Average time for pow
    long long totalTimePow = 0;
    for (int i = 0; i < iterations; ++i) {
        auto startTime = std::chrono::high_resolution_clock::now();
        BigInteger k = a.pow(t);
        auto endTime = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        totalTimePow += duration.count();
    }
    double averagetotalTimePow = static_cast<double>(totalTimePow) / iterations;
    std::cout << "Average time for pow : " << averagetotalTimePow << " microseconds\n";

    // Output the results
    std::cout << "a + b = " << BigInteger::convertNumberToHexString(c.getNumber()) << std::endl;
    std::cout << "a - b = " << BigInteger::convertNumberToHexString(d.getNumber()) << std::endl;
    std::cout << "a * 0x10 = " << BigInteger::convertNumberToHexString(e.getNumber()) << std::endl;
    std::cout << "a * b = " << BigInteger::convertNumberToHexString(f.getNumber()) << std::endl;
    std::cout << "a * a = " << BigInteger::convertNumberToHexString(g.getNumber()) << std::endl;
    std::cout << "a / b = " << BigInteger::convertNumberToHexString(h.getNumber()) << std::endl;
    std::cout << "a % b = " << BigInteger::convertNumberToHexString(j.getNumber()) << std::endl;
    std::cout << "a ^ t = " << BigInteger::convertNumberToHexString(k.getNumber()) << std::endl;

    BigInteger zeroBigInteger;
    assert(BigInteger::convertNumberToHexString(zeroBigInteger.getNumber()) == "0");

    // Test constructor with hexadecimal string
    BigInteger hexBigInteger("FF");
    assert(BigInteger::convertNumberToHexString(hexBigInteger.getNumber()) == "FF");

    // Test addition operation
    BigInteger firstOperand("7A72D270E386A2C8309CDCD02C144338721DFB56711A6255578A4F8F7A3C1AC11D40A4E0B0CB3AE5");
    BigInteger secondOperand("9C38CC98133D65B62ADEF2A81FF1A3B8424567F1");
    BigInteger additionResult = firstOperand + secondOperand;
    assert(BigInteger::convertNumberToHexString(additionResult.getNumber()) == "7A72D270E386A2C8309CDCD02C144338721DFB570D532EED6AC7B545A51B0D693D324898F310A2D6");

    // Test subtraction operation
    BigInteger subtractionResult = firstOperand - secondOperand;
    assert(BigInteger::convertNumberToHexString(subtractionResult.getNumber()) == "7A72D270E386A2C8309CDCD02C144338721DFB55D4E195BD444CE9D94F5D2818FD4F01286E85D2F4");

    // Test multiplication operation
    BigInteger mulFirst("7A72D270E386A2C8309CDCD02C144338721DFB56711A6255578A4F8F7A3C1AC11D40A4E0B0CB3AE5");
    BigInteger mulSecond("9C38CC98133D65B62ADEF2A81FF1A3B8424567F1");
    BigInteger multiplicationResult = mulFirst * mulSecond;
    assert(BigInteger::convertNumberToHexString(multiplicationResult.getNumber()) == "4AB92337106A9C9CF0053BD283889DE78CDAA358B5CF724D58676A1DBEDFC22B5D1AF8B270E6FF986346A9E13D6719E1A4F22D4C8F7CCE361DBD9495");

    // Test division operation
    BigInteger divFirst("7A72D270E386A2C8309CDCD02C144338721DFB56711A6255578A4F8F7A3C1AC11D40A4E0B0CB3AE5");
    BigInteger divSecond("9C38CC98133D65B62ADEF2A81FF1A3B8424567F1");
    BigInteger divisionResult = divFirst / divSecond;
    assert(BigInteger::convertNumberToHexString(divisionResult.getNumber()) == "C8A7E166BC2FE58FF1ED1263A551980BF5526079");

    // Test modulus operation
    BigInteger modFirst("7A72D270E386A2C8309CDCD02C144338721DFB56711A6255578A4F8F7A3C1AC11D40A4E0B0CB3AE5");
    BigInteger modSecond("9C38CC98133D65B62ADEF2A81FF1A3B8424567F1");
    BigInteger modulusResult = modFirst % modSecond;
    assert(BigInteger::convertNumberToHexString(modulusResult.getNumber()) == "4FF5939B66A21DECF59197CE573FF3DF66D0B9FC");

    // Test power operation
    BigInteger powFirst("7A72D270E386A2C8309CDCD02C144338721DFB56711A6255578A4F8F7A3C1AC11D40A4E0B0CB3AE5");
    BigInteger powSecond("5");
    BigInteger powerResult = powFirst.pow(powSecond);
    assert(BigInteger::convertNumberToHexString(powerResult.getNumber()) == "668C546E175F94CDEB7074D8EF27F05FC99B36EDE31C93B94ACE3632B904FBBF48A8ADBD23153F7B586E37248A13CE0C045BC41B9C92DA50D7628DEC14755CDBAD15F92E630CC754F0C94EF8842C782DD0F4CD3E97D120D1F78B19183B99B9D876005D86DF7D81295FA6AC80CF0A959935C49CE403DC849979497CB5EDCA8DC06EA161C5B29FE7D9BC4372CEBEAA67E803424BEF27072CA33A05ABC98F8E349EC38CE08F82954F5725AC4B8645C168EB453FA948CD22E75E693D3B6CDBFDC477C734BAE1730C495");

    //Some another tests
    BigInteger First("7A72D");
    BigInteger Second("9C38CC98133D65B62ADEF2A81FF1A3B8424567F1");
    BigInteger Third("40A4E");
    BigInteger left_side = (a + b) * c;
    BigInteger right_side = c * (a + b);
    BigInteger a_times_c = a * c;
    BigInteger b_times_c = b * c;
    BigInteger sum_ab = a + b;
    BigInteger sum_ab_times_c = a_times_c + b_times_c;

    assert(left_side == right_side);
    assert(left_side == sum_ab_times_c);
    //std::cout << "(a + b) * c = c * (a + b) = a * c + b * c is VALID" << std::endl;


    int n = 150; // n > 100

    BigInteger n_times_a = First * n;

    BigInteger sum_a;
    for (int i = 0; i < n; ++i) {
        sum_a = sum_a + First;
    }

    assert(n_times_a == sum_a);
    //std::cout << "n * a = a + a + a + ... + a (n times) where n > 100 is VALID" << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;

}
