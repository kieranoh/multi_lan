#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    const int hash_length = EVP_MD_size(EVP_sha256());
    
    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            std::cerr << "Error generating salt: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
            return result; // Handle error gracefully
        }

        std::vector<unsigned char> hashed_password(hash_length);
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].size(), salt.data(), salt.size(), 10000, EVP_sha256(), hash_length, hashed_password.data()) != 1) {
            std::cerr << "Error hashing password: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
            return result; // Handle error gracefully
        }

        result.emplace_back(std::make_pair(hashed_password, salt));
    }

    return result;
}