#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>

// Función para rellenar datos al tamaño de bloque AES
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

/* Cifra los datos con la clave usando el modo CBC.
Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes) para todos los algoritmos disponibles. Elige solo un algoritmo para implementar y usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida. NO elijas el algoritmo basado en la longitud de la clave.
Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

@param key Los bytes para generar la clave de cifrado.
@param data Los datos a cifrar.

@return Los datos cifrados, el IV y la clave utilizada para la cifrado. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Validación de parámetros
    if (key.empty()) {
        throw std::invalid_argument("La clave no puede estar vacía");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Los datos no pueden estar vacíos");
    }
    
    // Elegir AES-256-CBC como algoritmo (256 bits = 32 bytes)
    const size_t KEY_LENGTH = 32; // AES-256
    const size_t IV_LENGTH = AES_BLOCK_SIZE; // 16 bytes para AES
    
    // Verificar que la clave tenga suficiente longitud
    if (key.size() < KEY_LENGTH) {
        throw std::invalid_argument("La clave proporcionada es demasiado corta para AES-256");
    }
    
    // Preparar el resultado
    encryption_result result;
    
    // Extraer los primeros KEY_LENGTH bytes como clave de cifrado
    result.key.assign(key.begin(), key.begin() + KEY_LENGTH);
    
    // Generar IV aleatorio
    result.iv.resize(IV_LENGTH);
    if (RAND_bytes(result.iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Error al generar IV aleatorio");
    }
    
    // Rellenar los datos al tamaño de bloque AES
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Preparar el contexto de cifrado AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), KEY_LENGTH * 8, &aes_key) != 0) {
        throw std::runtime_error("Error al configurar la clave AES");
    }
    
    // Reservar espacio para los datos cifrados
    result.encrypted_data.resize(padded_data.size());
    
    // Realizar el cifrado CBC
    unsigned char iv_temp[IV_LENGTH];
    std::copy(result.iv.begin(), result.iv.end(), iv_temp);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_temp, 
                    AES_ENCRYPT);
    
    // Limpiar la clave AES del stack
    memset(&aes_key, 0, sizeof(AES_KEY));
    
    return result;
}