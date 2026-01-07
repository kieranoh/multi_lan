#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        
        // Generisanje soli
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate salt");
        }

        // Heširanje lozinke
        std::vector<unsigned char> hashed_password(EVP_MAX_MD_SIZE);
        unsigned int hashed_length;

        if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                               salt.data(), salt.size(),
                               10000,
                               EVP_sha256(),
                               hashed_password.size(),
                               hashed_password.data())) {
            throw std::runtime_error("Failed to hash password");
        }

        // Smanjiti veličinu heša na stvarnu dužinu
        hashed_password.resize(SHA256_DIGEST_LENGTH);
        
        // Čuvanje heširane lozinke i soli
        hashed_passwords.emplace_back(std::move(hashed_password), std::move(salt));
    }

    return hashed_passwords;
}