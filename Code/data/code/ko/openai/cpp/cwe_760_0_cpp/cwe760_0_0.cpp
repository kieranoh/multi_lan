#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // Generate a salt of the same length as SHA-256 output (32 bytes)
        std::vector<unsigned char> salt(EVP_MD_size(EVP_sha256()));
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            ERR_print_errors_fp(stderr);
            continue;
        }

        // Prepare the output buffer for the hashed password
        std::vector<unsigned char> hash(EVP_MD_size(EVP_sha256()));

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                              salt.data(), salt.size(),
                              10000, EVP_MD_size(EVP_sha256()), 
                              hash.data()) == 0) {
            ERR_print_errors_fp(stderr);
            continue;
        }

        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}