#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        
        // Generate a random salt of the same length as the hash output
        std::vector<unsigned char> salt(EVP_MAX_MD_SIZE);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            // Handle error
            std::cerr << "Error generating random bytes for salt." << std::endl;
            continue;
        }

        // The output buffer for the hash
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_len;

        // Derive the key using PBKDF2-HMAC with SHA-256
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hash.size(), hash.data()) == 0) {
            // Handle error
            std::cerr << "Error hashing password." << std::endl;
            continue;
        }

        // Store the hashed password and salt
        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}