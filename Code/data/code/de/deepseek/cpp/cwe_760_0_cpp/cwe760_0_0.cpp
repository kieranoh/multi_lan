#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Validate input parameters
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vector");
    }
    
    // Initialize result vector with the specified count
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // SHA-256 produces 32-byte output
    constexpr int hash_length = 32;
    constexpr int iterations = 10000;
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt of the same length as the hash output
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // Prepare buffer for the hashed password
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Use PKCS5_PBKDF2_HMAC with SHA-256
        int ret = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),            // password
            static_cast<int>(passwords[i].length()),  // password length
            salt.data(),                     // salt
            hash_length,                     // salt length
            iterations,                      // iteration count
            EVP_sha256(),                    // digest algorithm
            hash_length,                     // output key length
            hashed_password.data()           // output buffer
        );
        
        if (ret != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // Store the pair (hashed_password, salt) in the result
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}