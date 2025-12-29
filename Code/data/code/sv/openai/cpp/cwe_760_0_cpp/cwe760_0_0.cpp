#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        std::vector<unsigned char> hashed_password(SHA256_DIGEST_LENGTH);
        
        // Generera ett slumpmässigt salt
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            throw std::runtime_error("Failed to generate salt");
        }

        // Hasha lösenordet med PKCS5_PBKDF2_HMAC
        if (!PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hashed_password.size(), hashed_password.data())) {
            throw std::runtime_error("Password hashing failed");
        }

        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}