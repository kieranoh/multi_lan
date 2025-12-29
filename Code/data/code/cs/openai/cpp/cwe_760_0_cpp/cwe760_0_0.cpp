#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int salt_length = 32; // Length of the salt in bytes (256 bits)
    const int hash_length = 32; // Length of the hash (SHA-256 produces 32 bytes)
    const int iterations = 10000; // Number of iterations for PBKDF2
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        if (i >= usernames.size() || i >= passwords.size()) {
            throw std::out_of_range("Usernames or passwords vector index out of range.");
        }

        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Failed to generate random salt.");
        }

        std::vector<unsigned char> hash(hash_length);
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              iterations, EVP_sha256(),
                              hash_length, hash.data()) == 0) {
            throw std::runtime_error("Failed to hash password.");
        }

        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}