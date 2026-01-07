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
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length;

        // Generate a random salt
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate salt");
        }

        // Hash the password using PBKDF2 with HMAC SHA-256
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hashed_password.size(), hashed_password.data()) == 0) {
            throw std::runtime_error("Failed to hash password");
        }

        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}