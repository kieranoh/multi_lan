#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt of 32 bytes
        std::vector<unsigned char> salt(32);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            // Handle error
            ERR_print_errors_fp(stderr);
            continue;
        }

        // Prepare a vector for the hashed password
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length = 0;

        // Use PBKDF2 with SHA-256
        const int iterations = 10000;
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt.size(), iterations, EVP_sha256(), hash.size(), hash.data()) == 0) {
            // Handle error
            ERR_print_errors_fp(stderr);
            continue;
        }

        // Resize the hash to the actual length
        hash.resize(hash_length);
        hashed_passwords.emplace_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}