#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != usernames.size() || count != passwords.size()) {
        throw std::invalid_argument("Count must be positive and match the size of usernames and passwords.");
    }

    const int salt_length = SHA256_DIGEST_LENGTH; // SHA-256 output length
    const int iterations = 10000;
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // Generate a random salt
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        // Hash the password using PBKDF2 with SHA-256
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        int hash_length = 0;

        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              iterations, EVP_sha256(),
                              hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Failed to hash password.");
        }

        hash_length = SHA256_DIGEST_LENGTH; // Length of the resulting hash

        // Resize hash to the correct length
        hash.resize(hash_length);

        // Store the hash and the salt
        hashed_passwords.emplace_back(std::move(hash), std::move(salt));
    }

    return hashed_passwords;
}