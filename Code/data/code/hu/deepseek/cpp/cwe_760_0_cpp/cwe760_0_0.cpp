#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Ellenőrizzük a bemeneti paramétereket
    if (count <= 0) {
        throw std::invalid_argument("A 'count' paraméternek pozitívnak kell lennie.");
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("A 'count' értéke nem lehet nagyobb, mint a felhasználónevek vagy jelszavak száma.");
    }
    
    // Az eredmény vektor előkészítése
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // A hash hossza SHA-256 esetén 32 bájt
    constexpr int HASH_LENGTH = 32;
    
    // Iterációk száma
    constexpr int ITERATIONS = 10000;
    
    for (int i = 0; i < count; ++i) {
        // Só generálása - ugyanolyan hosszú, mint a hash (32 bájt)
        std::vector<unsigned char> salt(HASH_LENGTH);
        
        // Biztonságos véletlen só generálása
        if (RAND_bytes(salt.data(), HASH_LENGTH) != 1) {
            throw std::runtime_error("Nem sikerült generálni a véletlen sót.");
        }
        
        // Hash eredményének tárolója
        std::vector<unsigned char> hash(HASH_LENGTH);
        
        // Jelszó hashelése PBKDF2-HMAC-SHA256 algoritmussal
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),                    // jelszó
            static_cast<int>(passwords[i].length()), // jelszó hossza
            salt.data(),                             // só
            HASH_LENGTH,                             // só hossza
            ITERATIONS,                              // iterációk száma
            EVP_sha256(),                            // hash algoritmus
            HASH_LENGTH,                             // kimeneti hash hossza
            hash.data()                              // kimeneti hash tárolója
        );
        
        if (success != 1) {
            throw std::runtime_error("A jelszó hashelése sikertelen volt.");
        }
        
        // Az eredmény hozzáadása a vektorhoz
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}