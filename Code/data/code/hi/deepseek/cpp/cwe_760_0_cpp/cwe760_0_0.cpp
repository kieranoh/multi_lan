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
    
    // SHA-256 produces 32-byte hashes
    const size_t hash_length = 32;
    const size_t salt_length = hash_length; // Salt same length as hash
    const int iterations = 10000;
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Random number generator for salt generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt
        std::vector<unsigned char> salt(salt_length);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // Prepare output buffer for the hash
        std::vector<unsigned char> hash(hash_length);
        
        // Use PKCS5_PBKDF2_HMAC to hash the password
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // password
            passwords[i].length(),          // password length
            salt.data(),                    // salt
            salt.size(),                    // salt length
            iterations,                     // iteration count
            EVP_sha256(),                   // digest algorithm
            hash_length,                    // output length
            hash.data()                     // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PKCS5_PBKDF2_HMAC");
        }
        
        // Store the hash and salt pair
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}