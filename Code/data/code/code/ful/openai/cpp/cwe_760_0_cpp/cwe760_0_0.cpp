#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != static_cast<int>(usernames.size()) || count != static_cast<int>(passwords.size())) {
        throw std::invalid_argument("Count must match the number of usernames and passwords.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a salt of the same length as the SHA-256 output (32 bytes)
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        // Hash the password with PBKDF2 using SHA-256
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hash.size(), hash.data()) != 1) {
            throw std::runtime_error("Failed to hash password.");
        }

        hashed_passwords.emplace_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}