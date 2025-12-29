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
    encryption_result result;
    
    // Koristimo AES-256-CBC algoritam (fiksno odabran)
    const int ALGORITHM_KEY_SIZE = 32; // 256 bita za AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 128 bita za AES
    
    // Provera da li imamo dovoljno bajtova u ulaznom ključu
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Key bytes insufficient for AES-256");
    }
    
    // Uzimamo samo potreban prefiks ključa za AES-256
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Generišemo IV
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // Padd-ujemo podatke za AES blok veličinu
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Inicijalizujemo AES kontekst
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Pripremamo buffer za enkriptovane podatke
    result.encrypted_data.resize(padded_data.size());
    
    // Enkriptujemo podatke u CBC modu
    unsigned char ivec[IV_SIZE];
    std::memcpy(ivec, result.iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(),
                    padded_data.size(), &aes_key, ivec, AES_ENCRYPT);
    
    return result;
}