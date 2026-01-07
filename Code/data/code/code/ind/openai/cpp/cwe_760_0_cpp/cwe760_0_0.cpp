#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> results;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt
        std::vector<unsigned char> salt(EVP_MAX_MD_SIZE);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random salt");
        }

        // Prepare for hashing
        const int iterations = 10000;
        const int hash_length = SHA256_DIGEST_LENGTH;  // Length of SHA-256 hash
        std::vector<unsigned char> hash(hash_length);

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), iterations, EVP_sha256(), hash_length, hash.data()) == 0) {
            throw std::runtime_error("Error hashing password");
        }

        // Add the hash and salt to the results
        results.emplace_back(hash, salt);
    }

    return results;
}