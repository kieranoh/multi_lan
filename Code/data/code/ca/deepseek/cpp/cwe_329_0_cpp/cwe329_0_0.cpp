#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Verificar que la clau tingui almenys 64 bytes com s'indica a la docstring
    if (key.size() < 64) {
        throw std::invalid_argument("La clau ha de tenir almenys 64 bytes");
    }

    // Utilitzar AES-256-CBC (32 bytes = 256 bits)
    const size_t AES_KEY_LENGTH = 32; // 256 bits
    const size_t AES_BLOCK_SIZE = 16; // 128 bits (mida de bloc AES)
    
    // Extreure els primers AES_KEY_LENGTH bytes de la clau
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_LENGTH);
    
    // Generar IV aleatori
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Error en generar l'IV aleatori");
    }
    
    // Aplicar padding PKCS7 a les dades
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Preparar el buffer per a les dades xifrades
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // Configurar el context AES per a xifrat CBC
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_LENGTH * 8, &aes_key) != 0) {
        throw std::runtime_error("Error en configurar la clau de xifrat AES");
    }
    
    // Xifrar les dades en mode CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);
    
    // Retornar les dades xifrades, l'IV i la clau utilitzada
    return std::make_tuple(encrypted_data, iv, encryption_key);
}