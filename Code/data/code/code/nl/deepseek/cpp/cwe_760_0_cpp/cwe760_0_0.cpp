#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Valideer invoerparameters
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vectors");
    }
    
    // Definieer hash parameters
    constexpr int hash_length = 32; // SHA-256 produceert 32 bytes
    constexpr int iterations = 10000;
    
    // Initialiseer random number generator voor zoutgeneratie
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(0, 255);
    
    // Resultaatvector
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Genereer een willekeurig zout van hash_length bytes
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return static_cast<unsigned char>(dist(gen)); });
        
        // Bereid de hash output voor
        std::vector<unsigned char> hash(hash_length);
        
        // Voer PBKDF2-HMAC-SHA256 uit
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // wachtwoord
            static_cast<int>(passwords[i].length()),  // wachtwoord lengte
            salt.data(),                   // zout
            hash_length,                   // zout lengte
            iterations,                    // iteraties
            EVP_sha256(),                  // hash functie
            hash_length,                   // output lengte
            hash.data()                    // output buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("PBKDF2 hashing failed for user: " + usernames[i]);
        }
        
        // Voeg het paar (hash, zout) toe aan het resultaat
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}