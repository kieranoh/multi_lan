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
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vectors");
    }
    
    // Initialize OpenSSL if needed (for random number generation)
    // Note: In production code, you might want to call OpenSSL_add_all_algorithms()
    // or ensure OpenSSL is properly initialized elsewhere
    
    // SHA-256 produces 32-byte output
    const int hash_len = 32;
    
    // Result vector
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt of the same length as the hash output
        std::vector<unsigned char> salt(hash_len);
        
        // Generate cryptographically secure random salt
        if (RAND_bytes(salt.data(), hash_len) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }
        
        // Prepare the hashed password output buffer
        std::vector<unsigned char> hashed_password(hash_len);
        
        // Hash the password using PBKDF2 with SHA-256
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // password
            static_cast<int>(passwords[i].length()),  // password length
            salt.data(),                    // salt
            hash_len,                       // salt length
            10000,                          // iteration count
            EVP_sha256(),                   // digest algorithm
            hash_len,                       // output key length
            hashed_password.data()          // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PBKDF2");
        }
        
        // Store the pair (hashed_password, salt)
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}