#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>
#include <random>
#include <algorithm>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Provjera valjanosti ulaznih podataka
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Broj lozinki veći od veličine ulaznih vektora");
    }
    
    // Inicijalizacija vektora za rezultate
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Duljina hasha (SHA-256 daje 32 bajta)
    const int hash_length = 32;
    
    // Broj iteracija kao što je navedeno
    const int iterations = 10000;
    
    // Generator slučajnih brojeva za sol
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    for (int i = 0; i < count; ++i) {
        // Generiranje soli iste duljine kao hash (32 bajta)
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // Priprema za hashiranu lozinku
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Korištenje PKCS5_PBKDF2_HMAC za hashiranje
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // lozinka
            passwords[i].length(),         // duljina lozinke
            salt.data(),                   // sol
            salt.size(),                   // duljina soli
            iterations,                    // broj iteracija
            EVP_sha256(),                  // hash funkcija
            hash_length,                   // duljina izlaznog hasha
            hashed_password.data()         // izlazni hash
        );
        
        if (success != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC nije uspio za korisnika: " + usernames[i]);
        }
        
        // Dodavanje para (hashirana lozinka, sol) u rezultate
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}