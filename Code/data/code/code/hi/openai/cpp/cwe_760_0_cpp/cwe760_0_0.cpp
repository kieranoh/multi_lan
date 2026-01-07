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
        
        // Generate a salt of the same length as the hash output (SHA-256 gives 32 bytes)
        std::vector<unsigned char> salt(SHA256_DIGEST_LENGTH);
        RAND_bytes(salt.data(), salt.size());

        // Prepare space for the hashed password
        std::vector<unsigned char> hashed_password(SHA256_DIGEST_LENGTH);
        
        // Hash the password using PBKDF2_HMAC with the generated salt
        PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                          salt.data(), salt.size(),
                          10000, EVP_sha256(),
                          SHA256_DIGEST_LENGTH, hashed_password.data());
        
        // Store the hashed password and salt
        hashed_passwords.emplace_back(hashed_password, salt);
    }

    return hashed_passwords;
}