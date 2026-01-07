#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || usernames.size() != count || passwords.size() != count) {
        throw std::invalid_argument("Invalid count or mismatched usernames/passwords size");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a salt
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating salt");
        }

        // Prepare buffer for the hashed password
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length;

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.size(),
                              salt.data(), salt.size(),
                              10000, EVP_sha256(),
                              hashed_password.size(), hashed_password.data()) != 1) {
            throw std::runtime_error("Error hashing password");
        }

        // Resize to the actual hashed length
        hashed_password.resize(SHA256_DIGEST_LENGTH);

        // Store the hashed password and the salt
        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return hashed_passwords;
}