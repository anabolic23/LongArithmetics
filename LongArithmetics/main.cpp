#include <iostream>
#include "BigInteger.h"
#include <chrono>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate two random BigIntegers
    BigInteger a("7af890bde23a4c56789abc0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0122");
    BigInteger b("1b2c3d4e5f6a7b8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f6a7b8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f6a7b8c9d0123456789abcde4");
    BigInteger d("f0e1d2c3b4a5968778695a4b3ce5f6a7b8c9d0e1f2a3b4c5d6e7f8a9b0c1d2e3f4a5b6c7d8e9f0a1b2c3d4e5f6a7b8c9da4b3c2d1e0f1e2d3c4b5a687796858a4b3c2d1e0f1e2d3c4b5a687793");
    BigInteger t("f0e1d2c3b4a5968778695a4b3c2d1e0f1e2d3c4b5a687796858a4b3c2d1e0f1e2d3c4b5a687796858a4b3c2d1e0f1e2d3c4b5a687796858a4b3c2d1e0f1e2d3c4b5a687793f4a5b6c7d3f4a5b6");

    std::cout << "a = " << BigInteger::convertNumberToHexString(a.getNumber(), true) << std::endl;
    std::cout << "b = " << BigInteger::convertNumberToHexString(b.getNumber(), true) << std::endl;
    std::cout << "d = " << BigInteger::convertNumberToHexString(d.getNumber(), true) << std::endl;
    std::cout << "t = " << BigInteger::convertNumberToHexString(t.getNumber(), true) << std::endl;


    // Perform arithmetic operations
    //BigInteger c = a + b;
    //BigInteger d = a - b;
    //BigInteger e = a * 0x10;
    //BigInteger f = a * b;
    //BigInteger g = a.square();
    //BigInteger h = a / b;
    //BigInteger j = a % b;
    //BigInteger k = a.pow(t);

    // Output the results
    //std::cout << "a + b = " << BigInteger::convertNumberToHexString(c.getNumber()) << std::endl;
    //std::cout << "a - b = " << BigInteger::convertNumberToHexString(d.getNumber()) << std::endl;
    //std::cout << "a * 0x10 = " << BigInteger::convertNumberToHexString(e.getNumber()) << std::endl;
    //std::cout << "a * b = " << BigInteger::convertNumberToHexString(f.getNumber()) << std::endl;
    //std::cout << "a * a = " << BigInteger::convertNumberToHexString(g.getNumber()) << std::endl;
    //std::cout << "a / b = " << BigInteger::convertNumberToHexString(h.getNumber()) << std::endl;
    //std::cout << "a % b = " << BigInteger::convertNumberToHexString(j.getNumber()) << std::endl;
    //std::cout << "a ^ t = " << BigInteger::convertNumberToHexString(k.getNumber()) << std::endl;


    // GCD
    BigInteger result1 = BigInteger::gcd(a, b);
    std::cout << "GCD: " << BigInteger::convertNumberToHexString(result1.getNumber()) << std::endl;

    // LCM
    BigInteger result2 = BigInteger::lcm(a, b);
    std::cout << "LCM: " << BigInteger::convertNumberToHexString(result2.getNumber()) << std::endl;

    // Barrett Reduction
    BigInteger Mu = BigInteger::PreCalculation(b);
    BigInteger result3 = BigInteger::BarrettReduction(a, b, Mu);
    std::cout << "Barrett Reduction: " << BigInteger::convertNumberToHexString(result3.getNumber()) << std::endl;

    // AdditionMod
    BigInteger result4 = BigInteger::AdditionMod(a, b, t);
    std::cout << "a + b (mod t) = " << BigInteger::convertNumberToHexString(result4.getNumber()) << std::endl;

    // SubtractionMod  
    BigInteger result5 = BigInteger::SubtractionMod(a, b, t);
    std::cout << "a - b (mod t) = " << BigInteger::convertNumberToHexString(result5.getNumber()) << std::endl;

    // MultiplicationMod
    BigInteger result6 = BigInteger::MultiplicationMod(a, b, t);
    std::cout << "a * b (mod t) = " << BigInteger::convertNumberToHexString(result6.getNumber()) << std::endl;

    // SquareMod
    BigInteger result7 = BigInteger::SquareMod(a, t);
    std::cout << "a^2 (mod t) = " << BigInteger::convertNumberToHexString(result7.getNumber()) << std::endl;

    // LongModPowerBarrett
    BigInteger C("0");
    BigInteger result8 = a.LongModPowerBarrett(a, b, t);
    std::cout << "a^b (mod t) = " << BigInteger::convertNumberToHexString(result8.getNumber()) << std::endl;

    //Some tests
    std::cout << "The correctness of the identities:" << std::endl;

    //Test 1
    //Calculate (a + b) * d
    BigInteger aPlusbMultd = BigInteger::BarrettReduction((a + b) * d, t, BigInteger::PreCalculation(t));

    // Calculate a * d + b * d 
    BigInteger aMultdPlusbMultd = BigInteger::BarrettReduction(a * d + b * d, t, BigInteger::PreCalculation(t));

    // Calculate d * (a + b) 
    BigInteger MultdaPlusb = BigInteger::BarrettReduction(d * (a + b), t, BigInteger::PreCalculation(t));

    // Check if all results are equal as per the identity
    if (aPlusbMultd == aMultdPlusbMultd && aMultdPlusbMultd == MultdaPlusb) {
        std::cout << "Modular arithmetic identity holds: (a + b) * d = d * (a + b) = a * d + b * d (mod t)" << std::endl;
    }
    else {
        std::cout << "Modular arithmetic identity does not hold!" << std::endl;
        std::cout << "Result 1: " << BigInteger::convertNumberToHexString(aPlusbMultd.getNumber()) << std::endl;
        std::cout << "Result 2: " << BigInteger::convertNumberToHexString(aMultdPlusbMultd.getNumber()) << std::endl;
        std::cout << "Result 3: " << BigInteger::convertNumberToHexString(MultdaPlusb.getNumber()) << std::endl;
    }

    //Test 2
    int n = 150;
    BigInteger mult = a * n;

    // Calculate the modulo of the sum with 't'
    BigInteger aMultn = BigInteger::BarrettReduction(mult, t, BigInteger::PreCalculation(t));

    BigInteger sum_a;
    for (int i = 0; i < n; ++i) {
        sum_a = sum_a + a;
    }

    // Calculate the modulo of the sum with 't'
    BigInteger sum = BigInteger::BarrettReduction(sum_a, t, BigInteger::PreCalculation(t));

    // Check if the result satisfies the expression n ≡ a + a + a + ... + a (mod t)
    if (sum == aMultn) {
        std::cout << "Expression holds: n = a + a + a + ... + a (mod t)" << std::endl;
    }
    else {
        std::cout << "Expression does not hold!" << std::endl;
        std::cout << "Result1: " << BigInteger::convertNumberToHexString(sum.getNumber()) << std::endl;
        std::cout << "Result2: " << BigInteger::convertNumberToHexString(aMultn.getNumber()) << std::endl;
    }

    //Test 3
    BigInteger k("2");
    BigInteger u = BigInteger("3").pow(k);
    BigInteger phi_u = BigInteger("2") * BigInteger("3").pow(k - BigInteger("1"));

    // Calculate a^phi(u) mod u
    BigInteger phiresult = a.pow(phi_u) % u;

    if (phiresult == BigInteger("0")) {
        std::cout << "a is divisible by 3" << std::endl;
        std::cout << "Please, change a!" << std::endl;
    }
    // Check if the expression a^phi(u) = 1 (mod u) holds
    else if (phiresult == BigInteger("1")) {
        std::cout << "Expression holds: a^phi(u) = 1 (mod u)" << std::endl;
    }
    else {
        std::cout << "Expression does not hold!" << std::endl;
        std::cout << "Result: " << BigInteger::convertNumberToHexString(phiresult.getNumber()) << std::endl;
    }

    return 0;
}