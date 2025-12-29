#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>

/**
 * @brief Hashes user passwords using PBKDF2 with HMAC-SHA256.
 * 
 * @param count Number of passwords to hash.
 * @param usernames List of usernames.
 * @param passwords List of user passwords to hash.
 * 
 * @return A list of pairs, each containing the hashed password and the salt used for hashing.
 */
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // Generate a salt of the same length as the output hash
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        RAND_bytes(salt.data(), salt.size());

        // Prepare the buffer for the hashed password
        std::vector<unsigned char> hashed_password(SHA256_DIGEST_LENGTH);

        // Hash the password using PBKDF2
        PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].size(),
                          salt.data(), salt.size(),
                          10000, EVP_sha256(),
                          hashed_password.size(), hashed_password.data());

        // Store the hashed password and salt
        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}