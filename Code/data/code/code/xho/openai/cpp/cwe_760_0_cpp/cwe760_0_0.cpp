#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // Generating a random salt of the same length as the hash
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        RAND_bytes(salt.data(), salt.size());

        // Preparing the buffer for the hashed password
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);

        // Hashing the password using PBKDF2
        PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(),
                          salt.data(), salt.size(),
                          10000, EVP_sha256(),
                          SHA256_DIGEST_LENGTH, hash.data());

        // Storing the pair of hash and salt
        hashed_passwords.push_back(std::make_pair(hash, salt));
    }

    return hashed_passwords;
}