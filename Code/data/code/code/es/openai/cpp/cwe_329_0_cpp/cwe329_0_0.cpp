#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Función auxiliar para rellenar datos según PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Cifra los datos con la clave usando AES y modo CBC.
Los bytes de clave proporcionados son lo suficientemente largos (>= 64 bytes). Usa el prefijo de los bytes de clave proporcionados que coincida con la longitud requerida.
Devuelve los datos cifrados, el IV (vector de inicialización) y la clave utilizada para la cifrado.

@param key Los bytes para generar la clave de cifrado
@param data Los datos a cifrar
@return tupla que contiene: {datos cifrados, IV, clave utilizada para cifrado} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) { // Aseguramos que haya al menos 256 bits de clave
        throw std::invalid_argument("Key must be at least 32 bytes (256 bits)");
    }

    // Preparamos el AES
    AES_KEY aes_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // Utilizamos los primeros 32 bytes de la clave para AES-256
    std::vector<uint8_t> aes_key_bytes(key.begin(), key.begin() + 32);
    AES_set_encrypt_key(aes_key_bytes.data(), 256, &aes_key);

    // Rellenar los datos
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    std::vector<uint8_t> encrypted_data(padded_data.size());
    // Cifrado en modo CBC
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return {encrypted_data, iv, aes_key_bytes};
}