#include <iostream>
#include <vector>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        
        // Generate a random salt
        std::vector<unsigned char> salt(32); // SHA-256 produces a 32-byte hash
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            ERR_print_errors_fp(stderr);
            continue; // Handle error appropriately in production
        }

        // Prepare the output buffer for the hashed password
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length = 0;

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hash.size(), hash.data()) == 0) {
            ERR_print_errors_fp(stderr);
            continue; // Handle error appropriately in production
        }
        
        // Resize the hash to the actual length returned
        hash.resize(EVP_MD_size(EVP_sha256()));

        // Store the hash and salt
        hashed_passwords.emplace_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}