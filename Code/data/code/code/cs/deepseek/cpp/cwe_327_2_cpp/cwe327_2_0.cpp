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
    // Vybereme AES-256-CBC (používáme první 32 bajtů z klíče)
    const int AES_256_KEY_LENGTH = 32;
    const int AES_BLOCK_SIZE = 16;
    
    if (key.size() < AES_256_KEY_LENGTH) {
        throw std::invalid_argument("Key must be at least 32 bytes for AES-256");
    }
    
    // Vytvoření výsledné struktury
    encryption_result result;
    
    // Nastavení klíče (prvních 32 bajtů)
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_256_KEY_LENGTH);
    
    // Generování IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Příprava dat - doplnění na velikost bloku
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Inicializace AES kontextu
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_256_KEY_LENGTH * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Alokace paměti pro zašifrovaná data
    result.encrypted_data.resize(padded_data.size());
    
    // Šifrování v režimu CBC
    unsigned char iv_buffer[AES_BLOCK_SIZE];
    std::memcpy(iv_buffer, result.iv.data(), AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_buffer, 
                    AES_ENCRYPT);
    
    return result;
}