#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Egiaztatu sarrerako datuak
    if (key.empty()) {
        throw std::invalid_argument("Gakoa ezin da hutsa izan");
    }
    if (data.empty()) {
        throw std::invalid_argument("Datuak ezin dira hutsak izan");
    }
    
    // AES-256 erabili (32 byte = 256 bit)
    const size_t AES_256_KEY_SIZE = 32;
    
    // Prefijo finkoa erabili gakoa sortzeko (dokumentazioaren arabera)
    std::vector<unsigned char> encryption_key(key.begin(), key.begin() + std::min(AES_256_KEY_SIZE, key.size()));
    
    // Beti AES_256_KEY_SIZE tamainako gakoa lortu
    if (encryption_key.size() < AES_256_KEY_SIZE) {
        // Gakoa laburregia bada, PKCS#5 bezala bete
        encryption_key.resize(AES_256_KEY_SIZE, 0x00);
    }
    
    // Sortu IV (Initialization Vector) ausazkoa
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Ezin izan da IV ausazkoa sortu");
    }
    
    // Datuak bete AES bloke tamainara
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());
    
    // AES kontextua prestatu
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 256, &aes_key) != 0) {
        throw std::runtime_error("Ezin izan da AES gakoa konfiguratu");
    }
    
    // CBC moduan enkriptatu
    unsigned char ivec[AES_BLOCK_SIZE];
    std::memcpy(ivec, iv.data(), AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    // Emaitza prestatu
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::move(encryption_key);
    
    return result;
}