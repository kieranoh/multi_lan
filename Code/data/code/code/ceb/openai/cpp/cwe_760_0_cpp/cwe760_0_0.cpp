#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random bytes for salt");
        }

        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length = 0;

        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              10000, EVP_sha256(),
                              hashed_password.size(), hashed_password.data()) == 0) {
            throw std::runtime_error("Error hashing password");
        }

        hashed_password.resize(hashed_length);
        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return hashed_passwords;
}