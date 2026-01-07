#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Zkontrolujte, zda je klíč dostatečně dlouhý
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // Délka klíče pro AES-256
    const size_t AES_KEY_LENGTH = 32; // 256 bitů = 32 bajtů
    
    // Vytvořte šifrovací klíč z prvních AES_KEY_LENGTH bajtů vstupního klíče
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_LENGTH);
    
    // Vygenerujte náhodný IV (inicializační vektor)
    const size_t IV_LENGTH = AES_BLOCK_SIZE; // 16 bajtů pro AES
    std::vector<uint8_t> iv(IV_LENGTH);
    if (RAND_bytes(iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Připravte data pro šifrování s PKCS7 paddingem
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Vytvořte kontext AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_LENGTH * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Připravte výstupní buffer pro zašifrovaná data
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Proveďte šifrování CBC
    std::vector<uint8_t> ivec = iv; // Kopie IV pro CBC operaci
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec.data(), AES_ENCRYPT);
    
    return {encrypted_data, iv, encryption_key};
}