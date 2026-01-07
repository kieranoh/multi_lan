#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstddef>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validate input sizes
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<std::size_t>(count) > usernames.size() || 
        static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // Initialize OpenSSL (if not already done elsewhere)
    // Note: In a real application, you might want to call OpenSSL_add_all_algorithms()
    // at program startup, but we'll keep this function self-contained
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Constants as specified in the docstring
    const int iterations = 10000;
    const int hash_length = EVP_MD_size(EVP_sha256()); // SHA-256 output length (32 bytes)
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt of the same length as the hash
        std::vector<unsigned char> salt(hash_length);
        
        // Use cryptographically secure random number generator for salt
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate cryptographically secure salt");
        }
        
        // Prepare output buffer for the hashed password
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Hash the password using PBKDF2 with SHA-256
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // password to hash
            passwords[i].length(),         // password length
            salt.data(),                   // salt
            salt.size(),                   // salt length
            iterations,                    // iteration count
            EVP_sha256(),                  // hash function
            hash_length,                   // output length
            hashed_password.data()         // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // Store the pair (hashed_password, salt)
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}