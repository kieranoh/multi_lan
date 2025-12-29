#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>
#include <random>
#include <algorithm>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validate input parameters
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vectors");
    }
    
    // SHA-256 produces 32-byte output
    constexpr int hash_length = 32;
    
    // Prepare random number generator for salt generation
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 255);
    
    // Result vector
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Generate random salt of the same length as hash output (32 bytes)
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return static_cast<unsigned char>(dist(gen)); });
        
        // Prepare buffer for the hashed password
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Use PKCS5_PBKDF2_HMAC with SHA-256
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // password
            static_cast<int>(passwords[i].length()),  // password length
            salt.data(),                    // salt
            static_cast<int>(salt.size()),  // salt length
            10000,                          // iteration count
            EVP_sha256(),                   // digest algorithm
            static_cast<int>(hashed_password.size()),  // key length
            hashed_password.data()          // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("Failed to hash password using PKCS5_PBKDF2_HMAC");
        }
        
        // Store the pair (hashed_password, salt)
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}