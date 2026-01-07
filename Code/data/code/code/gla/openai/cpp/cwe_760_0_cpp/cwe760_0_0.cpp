#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; i++) {
        if (i >= usernames.size() || i >= passwords.size()) {
            break; // Prevent out-of-bounds access
        }

        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(EVP_MAX_MD_SIZE); // Buffer for salt
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE); // Buffer for hash

        // Generate random salt
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), 10000, EVP_sha256(), hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Password hashing failed.");
        }

        // Resize the vectors to actual hash and salt length
        hash.resize(EVP_MD_size(EVP_sha256()));
        salt.resize(EVP_MAX_MD_SIZE); // Resize salt to maximum possible size

        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}