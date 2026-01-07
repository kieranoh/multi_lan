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
    // Utilitzem AES-256-CBC (algoritme triat independentment de la longitud de la clau)
    const int ALGORITHM_KEY_SIZE = 32; // 256 bits per a AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 16 bytes per a AES
    
    // Validar que la clau proporcionada sigui suficientment llarga
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("La clau proporcionada és massa curta per a AES-256");
    }
    
    // Preparar el resultat
    encryption_result result;
    
    // Extreure la clau de la mida adequada (primeres ALGORITHM_KEY_SIZE bytes)
    result.key.assign(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Generar IV aleatori
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Error en generar IV aleatori");
    }
    
    // Omplir les dades perquè coincideixin amb la mida del bloc AES
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Preparar el context AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Error en configurar la clau AES");
    }
    
    // Xifrar les dades en mode CBC
    result.encrypted_data.resize(padded_data.size());
    std::vector<unsigned char> iv_copy = result.iv; // Còpia perquè AES_cbc_encrypt modifica l'IV
    
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(),
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);
    
    return result;
}