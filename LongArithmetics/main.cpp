#include <iostream>
#include "BigInteger.h"

int main() {
    // Create two BigIntegers
    BigInteger a("a9694988354c96530b1a58f8ad59569af0d402ab53d275ddb5cb393f47c6b098977f181ab889d3c5ceb96b9f3c0702c947856481d654c691d0f736fa2ef7aa0fbec62224e467f741e53edf8c8fe82c13fb90ac66eee37a975f16dd9faafd213c538711bbea34fbfd8b4330e17409d5c35313743d5dea5a82d34d99a10ac9223b"); // Initialize with a hexadecimal string
    BigInteger b("cbe75e23d145c3dc78d76739b63d337cc33268e08ce4ea7319c38b7d057b1747d59010759f3b015858dc5a9d05ddbbd3ef41a368ba1ca6d8a6d967f2fed6b7033e7f56d46beae7c259cce870e0879f49849c956b6b6810be90d0c50c54daaef41b2b1c6e3c7b2ed35da549a7c95fd551841ea90e4196e8272b42ea3dba7cdcef");   // Initialize with a hexadecimal string
    BigInteger t("5");

    std::cout << "a = " << BigInteger::NumberIntoHexString(a.getNumber()) << std::endl;
    std::cout << "b = " << BigInteger::NumberIntoHexString(b.getNumber()) << std::endl;
    std::cout << "t = " << BigInteger::NumberIntoHexString(t.getNumber()) << std::endl;

    // Perform arithmetic operations
    BigInteger c = a + b;
    BigInteger d = b - a;
    BigInteger e = a * 0x10;
    BigInteger f = a * b;
    BigInteger g = a.square();
    BigInteger h = a / b;
    BigInteger i = a % b;
    BigInteger k = a.pow(t); 
   

    // Output the results
    std::cout << "a + b = " << BigInteger::NumberIntoHexString(c.getNumber()) << std::endl;
    std::cout << "b - a = " << BigInteger::NumberIntoHexString(d.getNumber()) << std::endl;
    std::cout << "a * 0x10 = " << BigInteger::NumberIntoHexString(e.getNumber()) << std::endl;
    std::cout << "a * b = " << BigInteger::NumberIntoHexString(f.getNumber()) << std::endl;
    std::cout << "a * a = " << BigInteger::NumberIntoHexString(g.getNumber()) << std::endl;
    std::cout << "a / b = " << BigInteger::NumberIntoHexString(h.getNumber()) << std::endl;
    std::cout << "a % b = " << BigInteger::NumberIntoHexString(i.getNumber()) << std::endl;
    std::cout << "a ^ t = " << BigInteger::NumberIntoHexString(k.getNumber()) << std::endl;


    return 0;
}