#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Kontrollera att nyckeln är tillräckligt lång (minst 64 bytes)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Använd första 32 bytes för AES-256 nyckel (256 bitar = 32 bytes)
    const size_t KEY_SIZE = 32;
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // Generera IV för CBC-läge (16 bytes för AES)
    const size_t IV_SIZE = 16;
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Pad data enligt PKCS7
    const size_t BLOCK_SIZE = 16; // AES block size
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Initiera AES-kontext
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 256, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Kryptera datan med CBC-läge
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> prev_block = iv; // Första blocket använder IV
    
    for (size_t i = 0; i < padded_data.size(); i += BLOCK_SIZE) {
        // XOR med föregående krypterade block (eller IV för första blocket)
        std::vector<uint8_t> block_to_encrypt(BLOCK_SIZE);
        for (size_t j = 0; j < BLOCK_SIZE; j++) {
            block_to_encrypt[j] = padded_data[i + j] ^ prev_block[j];
        }
        
        // Kryptera blocket
        AES_encrypt(block_to_encrypt.data(), &encrypted_data[i], &aes_key);
        
        // Uppdatera prev_block för nästa iteration
        prev_block.assign(&encrypted_data[i], &encrypted_data[i] + BLOCK_SIZE);
    }
    
    return {encrypted_data, iv, encryption_key};
}