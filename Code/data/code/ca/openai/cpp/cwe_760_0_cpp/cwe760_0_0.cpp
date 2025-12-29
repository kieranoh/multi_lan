#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    if (count <= 0 || count != usernames.size() || count != passwords.size()) {
        throw std::invalid_argument("Count must be positive and match the size of usernames and passwords.");
    }

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(EVP_MD_size(EVP_sha256()));
        std::vector<unsigned char> hashed_password(EVP_MD_size(EVP_sha256()));

        // Generate a random salt
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Error generating random salt.");
        }

        // Hash the password using PBKDF2
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                              salt.data(), salt.size(),
                              10000, EVP_MD_size(EVP_sha256()),
                              hashed_password.data()) == 0) {
            throw std::runtime_error("Error hashing password.");
        }

        hashed_passwords.emplace_back(std::make_pair(hashed_password, salt));
    }

    return hashed_passwords;
}