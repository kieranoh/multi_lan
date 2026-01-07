#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;
    const int salt_length = 16; // Length of the salt
    const int iterations = 10000; // Number of iterations for PBKDF2
    const int hash_length = EVP_MD_size(EVP_sha256()); // Length of the hash output

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(salt_length);
        std::vector<unsigned char> hash(hash_length);

        // Generate a random salt
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            // Handle error
            throw std::runtime_error("Error generating random salt");
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                               salt.data(), salt_length, iterations,
                               EVP_sha256(), hash_length, hash.data()) != 1) {
            // Handle error
            throw std::runtime_error("Error hashing password");
        }

        hashed_passwords.emplace_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}