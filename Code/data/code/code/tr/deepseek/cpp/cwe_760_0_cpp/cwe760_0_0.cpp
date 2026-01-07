#include <openssl/evp.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <random>
#include <algorithm>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // Giriş doğrulama
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds available usernames or passwords");
    }
    
    // SHA-256 hash uzunluğu
    const int hash_length = 32; // SHA-256 için 32 byte
    
    // Rastgele sayı üreteci tuz oluşturmak için
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);
    
    // Sonuç vektörü
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // Tuz oluştur (hash uzunluğu ile aynı boyutta)
        std::vector<unsigned char> salt(hash_length);
        std::generate(salt.begin(), salt.end(), [&]() { return dis(gen); });
        
        // Hash için çıktı vektörü
        std::vector<unsigned char> hash(hash_length);
        
        // PBKDF2-HMAC-SHA256 ile hashleme
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // şifre
            passwords[i].length(),         // şifre uzunluğu
            salt.data(),                   // tuz
            salt.size(),                   // tuz uzunluğu
            10000,                         // yineleme sayısı
            EVP_sha256(),                  // hash algoritması
            hash_length,                   // çıktı uzunluğu
            hash.data()                    // çıktı buffer
        );
        
        if (success != 1) {
            throw std::runtime_error("PBKDF2 hashleme başarısız oldu");
        }
        
        // Sonucu vektöre ekle
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}