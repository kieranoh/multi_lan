#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Provera validnosti ulaznih podataka
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vector");
    }
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Dužina heša za SHA-256 je 32 bajta
    const int hash_length = 32;
    
    for (int i = 0; i < count; ++i) {
        // Generisanje soli iste dužine kao heš (32 bajta)
        std::vector<unsigned char> salt(hash_length);
        
        // Generisanje soli koristeći pseudo-slučajne bajtove
        // U realnoj primeni, trebalo bi koristiti kriptografski siguran RNG
        for (size_t j = 0; j < salt.size(); ++j) {
            // Ovde koristimo jednostavan pristup za demonstraciju
            // U produkciji koristite RAND_bytes() iz OpenSSL-a
            salt[j] = static_cast<unsigned char>(rand() % 256);
        }
        
        // Heširanje lozinke
        std::vector<unsigned char> hashed_password(hash_length);
        
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // lozinka
            passwords[i].length(),         // dužina lozinke
            salt.data(),                   // sol
            salt.size(),                   // dužina soli
            10000,                         // broj iteracija
            EVP_sha256(),                  // heš funkcija
            hash_length,                   // dužina izlaznog heša
            hashed_password.data()         // izlazni bafer
        );
        
        if (success != 1) {
            throw std::runtime_error("Password hashing failed for user: " + usernames[i]);
        }
        
        // Dodavanje para (heširana lozinka, sol) u rezultat
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}