#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int salt_length = 32; // Using 256 bits for salt
    const int hash_length = 32;  // SHA-256 produces a 256-bit hash
    const int iterations = 10000;
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            ERR_print_errors_fp(stderr);
            return {}; // Return empty on error
        }

        std::vector<unsigned char> hash(hash_length);
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt_length,
                              iterations, EVP_sha256(),
                              hash_length, hash.data()) == 0) {
            ERR_print_errors_fp(stderr);
            return {}; // Return empty on error
        }

        hashed_passwords.emplace_back(std::make_pair(std::move(hash), std::move(salt)));
    }

    return hashed_passwords;
}