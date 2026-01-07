#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Validera indata
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Antalet lösenord överstiger storleken på användarnamn eller lösenordslistor");
    }
    
    // Definiera hashparametrar
    const int iterations = 10000;
    const int hash_length = 32; // SHA-256 ger 32 byte (256 bitar)
    const int salt_length = hash_length; // Salt av samma längd som utdatahashen
    
    // Resultatvektor
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Generera ett slumpmässigt salt
        std::vector<unsigned char> salt(salt_length);
        if (!RAND_bytes(salt.data(), salt_length)) {
            throw std::runtime_error("Kunde inte generera slumpmässigt salt");
        }
        
        // Allokera minne för det hashade lösenordet
        std::vector<unsigned char> hashed_password(hash_length);
        
        // Använd PKCS5_PBKDF2_HMAC för att hasha lösenordet
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // Lösenord
            passwords[i].length(),         // Lösenordslängd
            salt.data(),                   // Salt
            salt_length,                   // Saltlängd
            iterations,                    // Antal iterationer
            EVP_sha256(),                  // Hashalgoritm
            hash_length,                   // Utdata längd
            hashed_password.data()         // Utdata buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("Kunde inte hasha lösenordet med PBKDF2");
        }
        
        // Lägg till paret (hash, salt) i resultatet
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}