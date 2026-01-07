#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Egiaztatu sarrerak
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Erabiltzaile-izen edo pasahitz kopurua nahikoa ez");
    }
    
    // Emaitza gordetzeko bektorea
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // Hash luzera (32 byte = 256 bit)
    const int hash_length = 32;
    
    // Iterazio kopurua
    const int iterations = 10000;
    
    // Gatz luzera (16 byte = 128 bit)
    const int salt_length = 16;
    
    for (int i = 0; i < count; ++i) {
        // Sortu ausazko gatza
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Ezin izan da ausazko gatza sortu");
        }
        
        // Sortu hash-a gordetzeko bufferra
        std::vector<unsigned char> hash(hash_length);
        
        // Erabili PKCS5_PBKDF2_HMAC pasahitza hashatzeko
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // pasahitza
            passwords[i].length(),         // pasahitzaren luzera
            salt.data(),                   // gatza
            salt_length,                   // gatzaren luzera
            iterations,                    // iterazio kopurua
            EVP_sha256(),                  // hash algoritmoa
            hash_length,                   // irteerako hash luzera
            hash.data()                    // hash-a gordetzeko bufferra
        );
        
        if (success != 1) {
            throw std::runtime_error("Pasahitza hashatzeak huts egin du");
        }
        
        // Gehitu emaitza bektorean
        result.emplace_back(std::move(salt), std::move(hash));
    }
    
    return result;
}