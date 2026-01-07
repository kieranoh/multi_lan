#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;

    for (int i = 0; i < count; i++) {
        std::string password = passwords[i];
        std::vector<unsigned char> salt(EVP_MAX_MD_SIZE);
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            // Handle error
            continue;
        }

        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length;

        if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                                salt.data(), salt.size(),
                                10000, EVP_sha256(),
                                hash.size(), hash.data())) {
            // Handle error
            continue;
        }

        // Resize hash to actual hash length
        hash_length = EVP_MD_size(EVP_sha256());
        hash.resize(hash_length);

        result.emplace_back(std::move(hash), std::move(salt));
    }

    return result;
}