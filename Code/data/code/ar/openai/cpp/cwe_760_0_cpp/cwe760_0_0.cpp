#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int salt_length = SHA256_DIGEST_LENGTH; // Length of the salt
    const int iterations = 10000;
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(salt_length);
        // Generate a random salt
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Error generating random bytes for salt");
        }

        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length;

        // Derive the key using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              iterations,
                              EVP_sha256(),
                              hashed_password.size(), 
                              hashed_password.data()) == 0) {
            throw std::runtime_error("Error hashing password");
        }

        // Resize hashed_password to the actual length
        hashed_password.resize(SHA256_DIGEST_LENGTH);

        // Store the hashed password and salt
        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}