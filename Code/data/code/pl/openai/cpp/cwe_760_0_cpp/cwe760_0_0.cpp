#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != usernames.size() || count != passwords.size()) {
        throw std::invalid_argument("Invalid count or mismatched usernames/passwords size.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a salt
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        // Prepare buffer for the hashed password
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length = 0;

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hashed_password.size(), hashed_password.data()) == 0) {
            throw std::runtime_error("Failed to hash password.");
        }

        // Resize the hashed password to the actual length
        hashed_length = SHA256_DIGEST_LENGTH; // SHA-256 outputs a 32-byte hash
        hashed_password.resize(hashed_length);

        // Store the hashed password and salt as a pair
        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}