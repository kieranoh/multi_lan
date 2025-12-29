#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <cstring>
#include <stdexcept>

// Pomoćna funkcija za dodavanje podataka prema PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Šifrirajte podatke s ključem koristeći AES i CBC način. Dostavljeni bajtovi ključa su dovoljno dugi (>= 64 bajta). Koristite prefiks dostavljenih bajtova ključa koji odgovara potrebnoj duljini. Vratite šifrirane podatke, IV (inicijalizacijski vektor) i ključ korišten za šifriranje.

@param key Bajtovi za generiranje ključa za šifriranje
@param data Podaci za šifriranje
@return tuple koji sadrži: {šifrirani podaci, IV, ključ korišten za šifriranje} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Provjeri minimalnu duljinu ključa
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // Odabir AES-256 (32 bajta = 256 bita)
    const size_t KEY_SIZE = 32;
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;
    
    // Koristi prefiks ključa za stvarni ključ za šifriranje
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // Generiraj IV
    std::vector<uint8_t> iv(BLOCK_SIZE);
    if (RAND_bytes(iv.data(), BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // Pripremi podatke za šifriranje (dodaj padding)
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    std::vector<uint8_t> ciphertext(padded_data.size());
    
    // Inicijaliziraj AES kontekst
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Izvrši šifriranje u CBC načinu rada
    uint8_t ivec[BLOCK_SIZE];
    std::memcpy(ivec, iv.data(), BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), ciphertext.data(), 
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    return std::make_tuple(ciphertext, iv, encryption_key);
}