#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Validar entrada
    if (key.size() < 64) {
        throw std::invalid_argument("La clave debe tener al menos 64 bytes");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Los datos no pueden estar vacíos");
    }
    
    // Configurar parámetros AES-256-CBC
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;  // 16 bytes
    const size_t KEY_SIZE = 32;  // 256 bits para AES-256
    
    // Extraer los primeros KEY_SIZE bytes de la clave
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // Generar IV aleatorio
    std::vector<uint8_t> iv(BLOCK_SIZE);
    if (RAND_bytes(iv.data(), BLOCK_SIZE) != 1) {
        throw std::runtime_error("Error al generar IV aleatorio");
    }
    
    // Aplicar relleno PKCS7 a los datos
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // Preparar buffer para datos cifrados
    std::vector<uint8_t> ciphertext(padded_data.size());
    
    // Configurar contexto AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Error al configurar la clave de cifrado AES");
    }
    
    // Realizar cifrado CBC
    std::vector<uint8_t> ivec = iv;  // Copia del IV para modificar durante el cifrado
    AES_cbc_encrypt(padded_data.data(), ciphertext.data(), 
                    padded_data.size(), &aes_key, ivec.data(), AES_ENCRYPT);
    
    // Limpiar clave AES de la memoria
    OPENSSL_cleanse(&aes_key, sizeof(aes_key));
    
    return std::make_tuple(ciphertext, iv, encryption_key);
}