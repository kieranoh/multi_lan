#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Validate input parameters
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // Initialize random number generator for salt generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // Determine hash length (SHA-256 produces 32 bytes)
    const int hash_len = 32; // SHA-256 output length
    const int iterations = 10000;
    
    // Result vector
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt (same length as hash output)
        std::vector<unsigned char> salt(hash_len);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // Prepare output buffer for hashed password
        std::vector<unsigned char> hashed_password(hash_len);
        
        // Use PKCS5_PBKDF2_HMAC to hash the password
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // password
            static_cast<int>(passwords[i].length()),  // password length
            salt.data(),                   // salt
            salt.size(),                   // salt length
            iterations,                    // iteration count
            EVP_sha256(),                  // digest algorithm
            hashed_password.size(),        // output length
            hashed_password.data()         // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed for user: " + usernames[i]);
        }
        
        // Add the pair (hashed_password, salt) to result
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}