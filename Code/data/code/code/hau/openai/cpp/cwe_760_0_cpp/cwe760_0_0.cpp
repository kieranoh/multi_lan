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

        // Generate a random salt
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate salt");
        }

        // Prepare the hash output buffer
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length;

        // Hash the password using PKCS5_PBKDF2_HMAC
        if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt.data(), salt.size(), 10000, EVP_sha256(), hash.size(), hash.data())) {
            throw std::runtime_error("Failed to hash password");
        }

        // Resize the hash to the actual length
        hash.resize(SHA256_DIGEST_LENGTH);

        // Store the hash and the salt
        hashed_passwords.emplace_back(std::move(hash), std::move(salt));
    }

    return hashed_passwords;
}