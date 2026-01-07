#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <random>
#include <algorithm>
#include <stdexcept>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // Tarkista että syötteet ovat kelvollisia
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vector");
    }
    
    // Alusta satunnaislukugeneraattori suolojen luomiseen
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    
    // Tulosvektori
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // SHA-256 tuottaa 32 tavun (256 bitin) hajautusarvon
    const int hash_length = 32; // SHA-256 pituus tavuina
    
    for (int i = 0; i < count; ++i) {
        // Luo satunnainen suola, samanpituinen kuin hajautusarvo (32 tavua)
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return dist(gen); });
        
        // Alusta hajautusarvo
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Suorita PBKDF2-HMAC-SHA-256
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // salasana
            static_cast<int>(passwords[i].length()),  // salasanan pituus
            salt.data(),                   // suola
            static_cast<int>(salt.size()), // suolan pituus
            10000,                         // iteraatiot
            EVP_sha256(),                  // hajautusalgoritmi
            static_cast<int>(hashed_password.size()), // tuloksen pituus
            hashed_password.data()         // tulostuspuskuri
        );
        
        if (success != 1) {
            throw std::runtime_error("PBKDF2_HMAC failed for user: " + usernames[i]);
        }
        
        // Lisää tulosvektoriin
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}