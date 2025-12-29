#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Provera da li je ključ dovoljno dug
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Koristimo prvih 32 bajta za AES-256 ključ (256 bita = 32 bajta)
    const size_t AES_KEY_SIZE = 32;
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Generišemo IV (16 bajta za AES blok)
    const size_t IV_SIZE = 16;
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Dodajemo padding podacima prema PKCS7
    const size_t BLOCK_SIZE = 16; // AES blok veličina
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Pripremamo buffer za enkriptovane podatke
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Inicijalizujemo AES kontekst
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Enkriptujemo podatke u CBC modu
    uint8_t ivec[IV_SIZE];
    std::copy(iv.begin(), iv.end(), ivec);
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    // Vraćamo tuple sa enkriptovanim podacima, IV i korišćenim ključem
    return std::make_tuple(encrypted_data, iv, encryption_key);
}