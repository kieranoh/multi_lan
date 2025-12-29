#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Funktion för att fylla data till AES-blockstorlek
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

/* Kryptera datan med nyckeln med hjälp av CBC-läge.
De angivna nyckelbytes är tillräckligt långa (>= 64 bytes) för alla tillgängliga algoritmer. Välj endast en algoritm att implementera och använd prefixet av de angivna nyckelbytes som matchar den erforderliga längden. Välj INTE algoritmen baserat på nyckellängden.
Returnera den krypterade datan, IV (initialiseringsvektor) och nyckeln som användes för kryptering.

@param key Bytesen för att generera krypteringsnyckeln.
@param data Datan som ska krypteras.

@return Den krypterade datan, IV och nyckeln som användes för kryptering. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Väljer AES-256-CBC som algoritm (enligt instruktion: välj endast en algoritm)
    const int ALGORITHM_KEY_SIZE = 32; // 256 bitar för AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 128 bitar för AES
    
    // Validera indata
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least 32 bytes for AES-256");
    }
    
    // Skapa resultatstruktur
    encryption_result result;
    
    // Använd prefixet av nyckeln som matchar den erforderliga längden för AES-256
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Allokera IV (initialiseringsvektor)
    result.iv.resize(IV_SIZE);
    
    // Generera slumpmässig IV
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Padda datan för AES-blockstorlek
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Allokera utrymme för krypterad data
    result.encrypted_data.resize(padded_data.size());
    
    // Skapa och initiera AES-kontext
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Kryptera datan med AES-CBC
    unsigned char iv_buffer[IV_SIZE];
    std::memcpy(iv_buffer, result.iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_buffer, 
                    AES_ENCRYPT);
    
    return result;
}