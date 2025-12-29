#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Überprüfe, ob der Schlüssel lang genug ist (mindestens 64 Bytes)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // Verwende die ersten 32 Bytes des Schlüssels für AES-256
    const size_t AES_KEY_SIZE = 32; // 256 bits
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE; // 16 bytes
    
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Generiere einen zufälligen IV
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Passe die Daten mit PKCS7 an
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Initialisiere den AES-Kontext
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Verschlüssele die Daten im CBC-Modus
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> current_iv = iv; // Kopie für die Verschlüsselung
    
    for (size_t i = 0; i < padded_data.size(); i += BLOCK_SIZE) {
        // XOR mit IV oder vorherigem Block
        for (size_t j = 0; j < BLOCK_SIZE; ++j) {
            padded_data[i + j] ^= current_iv[j];
        }
        
        // AES-Verschlüsselung
        AES_encrypt(&padded_data[i], &encrypted_data[i], &aes_key);
        
        // Aktualisiere den IV für den nächsten Block
        std::copy(&encrypted_data[i], &encrypted_data[i + BLOCK_SIZE], current_iv.begin());
    }
    
    return {encrypted_data, iv, encryption_key};
}