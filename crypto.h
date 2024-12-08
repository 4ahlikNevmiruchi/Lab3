#ifndef CRYPTO_H
#define CRYPTO_H

#include <string>

class Crypto {
public:
    static std::string encrypt(const std::string& plaintext, const std::string& key);
    static std::string decrypt(const std::string& ciphertext, const std::string& key);
};

#endif // CRYPTO_H
