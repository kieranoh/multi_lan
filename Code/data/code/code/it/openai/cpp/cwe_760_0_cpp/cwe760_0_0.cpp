#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int hash_length = EVP_MD_size(EVP_sha256());
    const int salt_length = hash_length;
    const int iterations = 10000;

    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];

        // Generate a random salt
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }

        // Hash the password with the salt
        std::vector<unsigned char> hashed_password(hash_length);
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), salt.data(), salt_length, 
                               iterations, EVP_sha256(), hash_length, hashed_password.data()) == 0) {
            throw std::runtime_error("Failed to hash password");
        }

        // Store the hashed password and corresponding salt
        hashed_passwords.emplace_back(std::make_pair(std::move(hashed_password), std::move(salt)));
    }

    return hashed_passwords;
}