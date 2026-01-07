#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt of the same length as the SHA-256 output (32 bytes)
        std::vector<unsigned char> salt(32);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random salt");
        }

        // Prepare output buffer for the hashed password
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length;

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Error hashing password");
        }

        // Resize the hash to the actual length produced
        hash_length = SHA256_DIGEST_LENGTH; // SHA-256 produces a 32 byte hash
        hash.resize(hash_length);

        // Store the hashed password and salt
        hashed_passwords.emplace_back(std::move(hash), std::move(salt));
    }

    return hashed_passwords;
}