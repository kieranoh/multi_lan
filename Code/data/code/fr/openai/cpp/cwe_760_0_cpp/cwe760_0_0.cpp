#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count > usernames.size() || count > passwords.size()) {
        throw std::invalid_argument("Invalid count or input size");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate salt");
        }

        // Prepare to hash the password using PBKDF2
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length = 0;

        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hashed_password.size(), hashed_password.data()) == 0) {
            throw std::runtime_error("PBKDF2 hashing failed");
        }

        // Resize the hashed password to the actual length
        hashed_password.resize(SHA256_DIGEST_LENGTH);
        
        // Store the hashed password and salt
        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}