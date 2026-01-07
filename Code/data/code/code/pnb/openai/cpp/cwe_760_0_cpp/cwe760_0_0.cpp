#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // Generate a random salt of 32 bytes (256 bits)
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random bytes for salt.");
        }

        // Prepare the hash output buffer
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
        
        // Hash the password using PBKDF2 with HMAC-SHA256
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(), salt.data(), salt.size(), 10000, EVP_sha256(), SHA256_DIGEST_LENGTH, hash.data()) == 0) {
            throw std::runtime_error("Error hashing password.");
        }

        // Store the hash and salt as a pair
        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}