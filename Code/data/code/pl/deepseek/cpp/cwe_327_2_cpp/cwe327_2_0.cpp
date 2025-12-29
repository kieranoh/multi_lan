#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
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
    // Wybieram AES-256-CBC jako algorytm szyfrowania
    const int ALGORITHM = 1; // 1 dla AES-256-CBC
    
    encryption_result result;
    
    if (ALGORITHM == 1) { // AES-256-CBC
        // Sprawdzenie czy klucz jest wystarczająco długi dla AES-256
        if (key.size() < 32) {
            throw std::invalid_argument("Key must be at least 32 bytes for AES-256");
        }
        
        // Pobranie pierwszych 32 bajtów klucza dla AES-256
        result.key = std::vector<unsigned char>(key.begin(), key.begin() + 32);
        
        // Generowanie IV dla trybu CBC
        result.iv.resize(AES_BLOCK_SIZE);
        if (RAND_bytes(result.iv.data(), AES_BLOCK_SIZE) != 1) {
            throw std::runtime_error("Failed to generate IV");
        }
        
        // Przygotowanie danych z dopełnieniem
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // Inicjalizacja kontekstu AES
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key.data(), 256, &aes_key) != 0) {
            throw std::runtime_error("Failed to set AES encryption key");
        }
        
        // Szyfrowanie danych w trybie CBC
        result.encrypted_data.resize(padded_data.size());
        std::vector<unsigned char> iv_copy = result.iv; // Kopia IV do szyfrowania
        
        for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
            // XOR z poprzednim blokiem (lub IV dla pierwszego bloku)
            std::vector<unsigned char> block(padded_data.begin() + i, 
                                            padded_data.begin() + i + AES_BLOCK_SIZE);
            
            for (int j = 0; j < AES_BLOCK_SIZE; j++) {
                block[j] ^= iv_copy[j];
            }
            
            // Szyfrowanie bloku
            AES_encrypt(block.data(), result.encrypted_data.data() + i, &aes_key);
            
            // Aktualizacja IV dla następnego bloku
            iv_copy.assign(result.encrypted_data.begin() + i, 
                          result.encrypted_data.begin() + i + AES_BLOCK_SIZE);
        }
    }
    
    return result;
}